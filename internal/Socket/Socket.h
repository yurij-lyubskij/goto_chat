//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_SOCKET_H
#define GOTO_CHAT_SOCKET_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <utility>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class iSocket {
public:

    virtual void async_read(beast::flat_buffer buffer, http::request<http::string_body> request,
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

    void async_read(beast::flat_buffer buffer, http::request<http::string_body> request,
                    std::function<void(std::error_code, unsigned long)> lamda) override {
        http::async_read(
                sock,
                buffer,
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
