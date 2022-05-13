//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_USERSESSION_H
#define GOTO_CHAT_USERSESSION_H

#include <string>
#include "Response.h"
#include "Acceptor.h"
#include "Request.h"
#include "Router.h"


class iUserSession {
public:
    virtual ~iUserSession() = default;

    virtual void writeResponse() = 0;

    virtual void readRequest() = 0;

    virtual void routeRequest() = 0;

    virtual Request createRequest() = 0;

    virtual void createResponse(Response response) = 0;
};


class UserSession : public std::enable_shared_from_this<UserSession>, iUserSession {
public:
    UserSession(std::shared_ptr<iSocket> socket,
                std::shared_ptr<iRouter> router)
            : socket(std::move(socket)), router(std::move(router)) {
    }

    // Initiate the asynchronous operations associated with the connection.
    void start() {
        readRequest();
    }

private:
    // The socket for the currently connected client.
    std::shared_ptr<iSocket> socket;
    std::shared_ptr<iRouter> router;
    // The buffer for performing reads.
    beast::flat_buffer buffer_{8192};
    // The request message.
    http::request<http::string_body> request_;

    // The response message.
    http::response<http::string_body> response_;

    // Asynchronously receive a complete request message.
    void readRequest() {
        auto self = shared_from_this();
        std::function lamda = [self](beast::error_code ec,
                                     std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec)
                self->routeRequest();
        };
        socket->async_read(
                buffer_,
                request_,
                lamda);
    }

    // Determine what needs to be done with the request message.
    void routeRequest() {
        Request request = createRequest();
        Response res;
        createResponse(res);
        writeResponse();
    }

    // Asynchronously transmit the response message.
    void writeResponse() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        std::function lamda = [self](beast::error_code ec, std::size_t) {
            self->socket->shutdown(ec);
        };

        socket->async_write(
                response_,
                lamda);
    }

    Request createRequest() {
        Request req;
        req.parameters["<field_name>"] = static_cast<std::string> (request_["<field_name>"]);
        req.method = static_cast<std::string>(request_.method_string());
        req.cookie = static_cast<std::string>(http::param_list(request_[http::field::cookie]).begin()->second);
        req.target = static_cast<std::string>(request_.target());
        req.body = static_cast<std::string>(request_.body());
        return req;
    }

    void createResponse(Response response) {
        response_.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response_.set(http::field::content_type, "text/plain");
        response_.set(http::field::cookie, response.cookie);
        response_.keep_alive(false);
        response_.body() = response_.body();
        response_.result(response.statusCode);
    }
};

#endif //GOTO_CHAT_USERSESSION_H
