//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_ACCEPTOR_H
#define GOTO_CHAT_ACCEPTOR_H
#include "Socket.h"

class iAcceptor {
public:
    iAcceptor() = default;

    virtual ~iAcceptor() = default;

    virtual void open(error_code ec) = 0;

    virtual void set_option(bool reuse, error_code ec) = 0;

    virtual void bind(error_code ec) = 0;

    virtual void listen(error_code ec) = 0;

    virtual void async_accept(std::shared_ptr<iSocket> socket, std::function<void(error_code ec)> lamda) = 0;
};


class Acceptor : public iAcceptor {
    tcp::acceptor acceptor_;
    tcp::endpoint endpoint;
    net::io_context &ioc;
public:
//    Acceptor(net::io_context &ioc, tcp::endpoint endpoint) : acceptor_(net::make_strand(ioc)),
//                                                             endpoint(std::move(endpoint))
//                                                              {};
    Acceptor(net::io_context &ioc, tcp::endpoint endpoint) : ioc(ioc), acceptor_(ioc),
                                                             endpoint(std::move(endpoint))
                                                              {};

    void open(error_code ec) override {
        acceptor_.open(endpoint.protocol(), ec);
    };

    void set_option(bool reuse, error_code ec) override {
        acceptor_.set_option(net::socket_base::reuse_address(reuse), ec);
    };

    void bind(error_code ec) override {
        acceptor_.bind(endpoint, ec);
    };

    void listen(error_code ec) override {
        acceptor_.listen(
                net::socket_base::max_listen_connections, ec);
    };

    void async_accept(std::shared_ptr<iSocket> socket, std::function<void(error_code ec)> lamda) override {
        acceptor_.async_accept((std::static_pointer_cast<Socket>(socket)) ->sock, lamda);
    }
};

class reAcceptor : public iAcceptor {
public:
    void open(error_code ec) override {
    };

    void set_option(bool reuse, error_code ec) override {
    };

    void bind(error_code ec) override {

    };

    void listen(error_code ec) override {

    };

    void async_accept(std::shared_ptr<iSocket> socket, std::function<void(error_code ec)> lamda) override {
    }
};

#endif //GOTO_CHAT_ACCEPTOR_H
