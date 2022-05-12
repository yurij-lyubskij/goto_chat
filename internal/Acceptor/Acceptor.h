//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_ACCEPTOR_H
#define GOTO_CHAT_ACCEPTOR_H

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

class iAcceptor {
public:
    iAcceptor() = default;

    virtual ~iAcceptor() = default;

    virtual void open(beast::error_code ec) = 0;

    virtual void set_option(bool reuse, beast::error_code ec) = 0;

    virtual void bind(beast::error_code ec) = 0;

    virtual void listen(beast::error_code ec) = 0;

    virtual void async_accept(tcp::socket &socket, std::function<void(beast::error_code ec)> lamda) = 0;
};

    class Acceptor: public iAcceptor{
        tcp::acceptor acceptor_;
        tcp::endpoint endpoint;
        net::io_context &ioc;
    public:
        Acceptor(net::io_context &ioc, tcp::endpoint endpoint) : acceptor_(net::make_strand(ioc)), endpoint(std::move(endpoint)),
                                                                 ioc(ioc) {};

        void open(beast::error_code ec) override {
            acceptor_.open(endpoint.protocol(), ec);
        };

        void set_option(bool reuse, beast::error_code ec) override {
            acceptor_.set_option(net::socket_base::reuse_address(reuse), ec);
        };

        void bind(beast::error_code ec) override {
            acceptor_.bind(endpoint, ec);
        };

        void listen(beast::error_code ec) override {
            acceptor_.listen(
                    net::socket_base::max_listen_connections, ec);
        };

        void async_accept(tcp::socket &socket, std::function<void(beast::error_code ec)> lamda) override {
            acceptor_.async_accept(socket, lamda);
        }
    };


#endif //GOTO_CHAT_ACCEPTOR_H
