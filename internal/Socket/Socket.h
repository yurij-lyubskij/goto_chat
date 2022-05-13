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

//typedef tcp::socket Socket;

class Socket {
public:
    tcp::socket &sock;

    explicit Socket(tcp::socket &sock) : sock(sock) {};

    void async_read(beast::flat_buffer buffer, http::request<http::dynamic_body> request,
                    std::function<void(boost::system::error_code, unsigned long)> lamda) {
        http::async_read(
                sock,
                buffer,
                request,
                lamda);
    }
    void async_write(const http::response<http::dynamic_body>& response,
                    std::function<void(boost::system::error_code, unsigned long)> lamda) {
        http::async_write(
                sock,
                response,
                lamda);
    }

    void shutdown(beast::error_code ec) {
        sock.shutdown(tcp::socket::shutdown_send, ec);
    }

};

#endif //GOTO_CHAT_SOCKET_H
