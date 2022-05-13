//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_SOCKET_H
#define GOTO_CHAT_SOCKET_H
#include "RequestBuffer.h"


class iSocket {
public:

    virtual void async_read(RequestBuffer buffer, http::request<http::string_body> request,
                            std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void async_write(const http::response<http::string_body> &response,
                             std::function<void(std::error_code, unsigned long)> lamda) = 0;

    virtual void shutdown(std::error_code ec) = 0;

    virtual ~iSocket() = default;
};

class Socket : public iSocket {
public:
    tcp::socket &sock;

    explicit Socket(tcp::socket &sock) : sock(sock) {};

    void async_read(RequestBuffer buffer, http::request<http::string_body> request,
                    std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_read(
                sock,
                buffer.buff,
                request,
                lamda);
    }

    void async_write(const http::response<http::string_body> &response,
                     std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_write(
                sock,
                response,
                lamda);
    }

    void shutdown(std::error_code ec) override {
        boost::system::error_code err;
        sock.shutdown(tcp::socket::shutdown_send, err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    }

};

#endif //GOTO_CHAT_SOCKET_H
