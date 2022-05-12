//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_ACCEPTOR_H
#define GOTO_CHAT_ACCEPTOR_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
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

class Listener;

class Acceptor {
    tcp::acceptor acceptor_;
    tcp::endpoint endpoint;
    net::io_context& ioc;
public:
    Acceptor(net::io_context& ioc, tcp::endpoint endpoint): acceptor_(net::make_strand(ioc)), endpoint(endpoint), ioc(ioc) {};
    void open(beast::error_code ec) {
        acceptor_.open(endpoint.protocol(), ec);
    };
    void set_option(bool reuse, beast::error_code ec) {
        acceptor_.set_option(net::socket_base::reuse_address(reuse), ec);
    };
    void bind(beast::error_code ec) {
        acceptor_.bind(endpoint, ec);
    };
    void listen(beast::error_code ec) {
        acceptor_.listen(
                net::socket_base::max_listen_connections, ec);
    };


    void async_accept(beast::detail::bind_front_wrapper<std::decay<void (Listener::*)(beast::error_code,
                                                                                      tcp::socket)>::type, std::shared_ptr<Listener>> wrapper) {
                acceptor_.async_accept(
                net::make_strand(ioc),
                 wrapper
               )

    }
};


#endif //GOTO_CHAT_ACCEPTOR_H
