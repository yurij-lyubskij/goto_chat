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
#include "httpBuffer.h"

const int16_t Unauthorized = 401;

class iUserSession {
public:
    virtual ~iUserSession() = default;

    virtual void writeResponse() = 0;

    virtual void readRequest() = 0;

    virtual void processRequest() = 0;

};


class UserSession : public std::enable_shared_from_this<UserSession>, iUserSession {
public:
    UserSession(std::shared_ptr<iSocket> socket,
                std::shared_ptr<iRouter> router)
            : socket(std::move(socket)), router(std::move(router)) {
        buff;
    }

    // Initiate the asynchronous operations associated with the connection.
    void start() {
        readRequest();
    }

private:
    // The socket for the currently connected client.
    std::shared_ptr<iSocket> socket;
    std::shared_ptr<iRouter> router;
    httpBuffer buff;
    // Asynchronously receive a complete request message.
    void readRequest() {
        auto self = shared_from_this();
        std::function lamda = [self](std::error_code ec,
                                     std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec)
                self->processRequest();
        };
        socket->async_read(
                buff,
                lamda);
    }

    // Determine what needs to be done with the request message.
    void processRequest() {
        Request request = buff.createRequest();
        request = router->UseMiddle(request);
        Response res;
        res.statusCode = request.responseStatus;
        if (request.responseStatus != Unauthorized) {
            res = router->Route(request);
        }
        buff.createResponse(res);
        writeResponse();
    }

    // Asynchronously transmit the response message.
    void writeResponse() {
        auto self = shared_from_this();

        buff.response_.content_length(buff.response_.body().size());

        std::function lamda = [self](std::error_code ec, std::size_t) {
            self->socket->shutdown(ec);
        };

        socket->async_write(
                buff,
                lamda);
    }

};

#endif //GOTO_CHAT_USERSESSION_H
