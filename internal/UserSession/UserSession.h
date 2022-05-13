//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_USERSESSION_H
#define GOTO_CHAT_USERSESSION_H

#include <string>
#include "Acceptor.h"

class iUserSession {
public:
    virtual ~iUserSession() = default;
    virtual void write_response() = 0;
    virtual void read_request() = 0;
    virtual void route_request() = 0;
};



class UserSession : public std::enable_shared_from_this<UserSession>, iUserSession {
public:
    UserSession(std::shared_ptr<iSocket> socket)
            : socket(std::move(socket)) {
    }
    // Initiate the asynchronous operations associated with the connection.
    void
    start() {
        read_request();
    }

private:
    // The socket for the currently connected client.
    std::shared_ptr<iSocket> socket;

    // The buffer for performing reads.
    beast::flat_buffer buffer_{8192};

    // The request message.
    http::request<http::dynamic_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // Asynchronously receive a complete request message.
    void read_request() {
        auto self = shared_from_this();
        std::function lamda = [self](beast::error_code ec,
                            std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec)
                self->route_request();
        };
        socket->async_read(
                buffer_,
                request_,
                lamda);
    }

    // Determine what needs to be done with the request message.
    void route_request() {
        response_.version(request_.version());
        response_.keep_alive(false);

        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
//                create_response();
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

    // Asynchronously transmit the response message.
    void write_response() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        std::function lamda = [self](beast::error_code ec, std::size_t) {
                    self->socket->shutdown(ec);
        };

        socket->async_write(
                response_,
                lamda);
    }
};

#endif //GOTO_CHAT_USERSESSION_H
