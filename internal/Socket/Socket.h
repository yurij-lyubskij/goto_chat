//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_SOCKET_H
#define GOTO_CHAT_SOCKET_H
#include "httpBuffer.h"


class iSocket {
public:

    virtual void async_read(httpBuffer buffer,
                            std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void async_write(httpBuffer buffer,
                             std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void shutdown(std::error_code ec) = 0;

    virtual ~iSocket() = default;
};

class Socket : public iSocket {
public:
    tcp::socket &sock;

    explicit Socket(tcp::socket &sock) : sock(sock) {};

    void async_read(httpBuffer buffer,
                    std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_read(
                sock,
                buffer.buff,
                buffer.request_,
                lamda);
    }

    void async_write(httpBuffer buffer,
                     std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_write(
                sock,
                buffer.response_,
                lamda);
    }

    void shutdown(std::error_code ec) override {
        boost::system::error_code err;
        sock.shutdown(tcp::socket::shutdown_send, err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    }

};

#endif //GOTO_CHAT_SOCKET_H
