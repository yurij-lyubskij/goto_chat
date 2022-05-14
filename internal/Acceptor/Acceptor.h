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

    virtual void open(std::error_code ec) = 0;

    virtual void set_option(bool reuse, std::error_code ec) = 0;

    virtual void bind(std::error_code ec) = 0;

    virtual void listen(std::error_code ec) = 0;

    virtual void async_accept(std::shared_ptr<iSocket> socket, std::function<void(std::error_code ec)> lamda) = 0;
};


class Acceptor : public iAcceptor {
    tcp::acceptor acceptor_;
    tcp::endpoint endpoint;
public:
    Acceptor(net::io_context &ioc, tcp::endpoint endpoint) : acceptor_(net::make_strand(ioc)),
                                                             endpoint(std::move(endpoint))
                                                              {};

    void open(std::error_code ec) override {
        boost::system::error_code err;
        acceptor_.open(endpoint.protocol(), err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    };

    void set_option(bool reuse, std::error_code ec) override {
        boost::system::error_code err;
        acceptor_.set_option(net::socket_base::reuse_address(reuse), err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    };

    void bind(std::error_code ec) override {
        boost::system::error_code err;
        acceptor_.bind(endpoint, err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    };

    void listen(std::error_code ec) override {
        boost::system::error_code err;
        acceptor_.listen(
                net::socket_base::max_listen_connections, err);
        ec = std::make_error_code(static_cast<std::errc>(err.value()));
    };

    void async_accept(std::shared_ptr<iSocket> socket, std::function<void(std::error_code ec)> lamda) override {
        acceptor_.async_accept((std::static_pointer_cast<Socket>(socket)) ->sock, lamda);
    }
};

class reAcceptor : public iAcceptor {
public:
    void open(std::error_code ec) override {
    };

    void set_option(bool reuse, std::error_code ec) override {
    };

    void bind(std::error_code ec) override {

    };

    void listen(std::error_code ec) override {

    };

    void async_accept(std::shared_ptr<iSocket> socket, std::function<void(std::error_code ec)> lamda) override {
    }
};

#endif //GOTO_CHAT_ACCEPTOR_H
