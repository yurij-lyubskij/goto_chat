//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_SOCKET_H
#define GOTO_CHAT_SOCKET_H
#include "httpBuffer.h"


class iSocket {
public:

    virtual void async_read(std::shared_ptr<IhttpBuffer> buffer,
                            std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void async_write(std::shared_ptr<IhttpBuffer> buffer,
                             std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void shutdown(std::error_code ec) = 0;

    virtual ~iSocket() = default;
};

class Socket : public iSocket {
public:
    tcp::socket &sock;

    explicit Socket(tcp::socket &sock) : sock(sock) {};

    void async_read(std::shared_ptr<IhttpBuffer> buffer,
                    std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_read(
                sock,
                std::static_pointer_cast<httpBuffer>(buffer)->buff,
                std::static_pointer_cast<httpBuffer>(buffer)->request_,
                lamda);
    }

    void async_write(std::shared_ptr<IhttpBuffer> buffer,
                     std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_write(
                sock,
                std::static_pointer_cast<httpBuffer>(buffer)->response_,
                lamda);
    }

    void shutdown(std::error_code ec) override {
        boost::system::error_code err;
        sock.shutdown(tcp::socket::shutdown_send, err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    }

};

class reSocket : public iSocket {
public:
    void async_read(std::shared_ptr<IhttpBuffer> buffer,
                    std::function<void(std::error_code, unsigned long)> lamda) override {

    }

    void async_write(std::shared_ptr<IhttpBuffer> buffer,
                     std::function<void(std::error_code, unsigned long)> lamda) override {
    }

    void shutdown(std::error_code ec) override {

    }

};

#endif //GOTO_CHAT_SOCKET_H
