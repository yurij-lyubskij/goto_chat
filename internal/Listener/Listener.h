//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_LISTENER_H
#define GOTO_CHAT_LISTENER_H

#include "Acceptor.h"

class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    http_connection(tcp::socket socket)
            : socket_(std::move(socket)) {
    }

    // Initiate the asynchronous operations associated with the connection.
    void
    start() {
        read_request();
        check_deadline();
    }

private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    beast::flat_buffer buffer_{8192};

    // The request message.
    http::request<http::dynamic_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{
            socket_.get_executor(), std::chrono::seconds(60)};

    // Asynchronously receive a complete request message.
    void
    read_request() {
        auto self = shared_from_this();

        http::async_read(
                socket_,
                buffer_,
                request_,
                [self](beast::error_code ec,
                       std::size_t bytes_transferred) {
                    boost::ignore_unused(bytes_transferred);
                    if (!ec)
                        self->process_request();
                });
    }

    // Determine what needs to be done with the request message.
    void
    process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);

        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
                create_response();
                break;

            default:
                // We return responses indicating an error if
                // we do not recognize the request method.
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body())
                        << "Invalid request-method '"
                        << std::string(request_.method_string())
                        << "'";
                break;
        }

        write_response();
    }

    // Construct a response message based on the program state.
    void
    create_response() {
        if (request_.target() == "/count") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                    << "<html>\n"
                    << "<head><title>Request count</title></head>\n"
                    << "<body>\n"
                    << "<h1>Request count</h1>\n"
                    << "<p>There have been "
                    //                    << my_program_state::request_count()
                    << " requests so far.</p>\n"
                    << "</body>\n"
                    << "</html>\n";
        } else if (request_.target() == "/time") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                    << "<html>\n"
                    << "<head><title>Current time</title></head>\n"
                    << "<body>\n"
                    << "<h1>Current time</h1>\n"
                    << "<p>The current time is "
                    //                    << my_program_state::now()
                    << " seconds since the epoch.</p>\n"
                    << "</body>\n"
                    << "</html>\n";
        } else {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "File not found\r\n";
        }
    }

    // Asynchronously transmit the response message.
    void
    write_response() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(
                socket_,
                response_,
                [self](beast::error_code ec, std::size_t) {
                    self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                    self->deadline_.cancel();
                });
    }

    // Check whether we have spent enough time on this connection.
    void
    check_deadline() {
        auto self = shared_from_this();

        deadline_.async_wait(
                [self](beast::error_code ec) {
                    if (!ec) {
                        // Close socket to cancel any outstanding operation.
                        self->socket_.close(ec);
                    }
                });
    }
};




class iListener {
public:
    iListener() = default;

    // Start accepting incoming connections
    virtual void run() = 0;

    virtual ~iListener() = default;

private:
    virtual void do_accept() = 0;

    virtual void on_accept(beast::error_code ec, tcp::socket socket) = 0;
};

class Listener : public std::enable_shared_from_this<Listener>, public iListener {
    net::io_context &ioc_;
    Acceptor &acceptor_;
public:

    static void fail(beast::error_code ec, char const *what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    Listener(
            net::io_context &ioc,
            Acceptor &acceptor
    )
            : ioc_(ioc), acceptor_(acceptor){
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(true, ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run() {
        do_accept();
    }

private:
    void
    do_accept() override {
        tcp::socket socket{ioc_};
        std::function lamda  = [&](beast::error_code ec)
        {
            if(!ec)
                on_accept(ec, std::move(socket));
        };
        acceptor_.async_accept(socket, lamda);
    }

    void on_accept(beast::error_code ec, tcp::socket socket) override {
        if (ec) {
            fail(ec, "accept");
            return; // To avoid infinite loop
        } else {
            // Create the session and run it
            std::make_shared<http_connection>(std::move(socket))->start();
        }

        // Accept another connection
        do_accept();
    }
};


#endif //GOTO_CHAT_LISTENER_H
