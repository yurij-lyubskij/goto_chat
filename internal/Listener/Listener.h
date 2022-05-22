//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_LISTENER_H
#define GOTO_CHAT_LISTENER_H

#include <utility>

//#include "Acceptor.h"
#include "Socket.h"
#include "UserSession.h"

class iListener {
public:

    // Start accepting incoming connections
    virtual void run() = 0;

    virtual ~iListener() = default;

private:
    virtual void do_accept() = 0;

    virtual void on_accept(error_code ec) = 0;
};

class Listener : public std::enable_shared_from_this<Listener>, public iListener {
//    std::shared_ptr<iAcceptor> acceptor_;
    tcp::acceptor acceptor_;
    tcp::endpoint endpoint;
    net::io_context &ioc;
    std::shared_ptr<iSocket>& sock;
    std::shared_ptr<iRouter> router;
    std::shared_ptr<iBufferFabric> fabric;
    static void fail(error_code ec, char const *what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }

public:
    Listener(const  Listener&) = delete;
    Listener& operator=(const  Listener&) = delete;

    Listener(
            std::shared_ptr<iSocket>& sock,
            net::io_context &ioc, tcp::endpoint endpoint,
            std::shared_ptr<iRouter> router,
            std::shared_ptr<iBufferFabric> fabric
    )
            : acceptor_(ioc), router(std::move(router)), fabric(std::move(fabric)), ioc(ioc),
    endpoint(std::move(endpoint)), sock(sock){
         error_code ec;
        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
                net::socket_base::max_listen_connections, ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void run() {
        do_accept();
    }

private:
    void
    do_accept() override {
        auto self = shared_from_this();
//        static std::function lamda = [self](error_code ec) {
//            if (!ec)
//                self->on_accept(ec);
//        };
        acceptor_.async_accept((std::static_pointer_cast<Socket>(sock))->sock, beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
    }

    void on_accept(error_code ec) override {
        auto self = shared_from_this();
        if (ec) {
            fail(ec, "accept");
            return; // To avoid infinite loop
        } else {
            // Create the session and run it
            std::make_shared<UserSession>(sock, router, fabric->make())->start();
        }
        // Accept another connection
        do_accept();
//        ioc.post(do_accept());
    }
};


#endif //GOTO_CHAT_LISTENER_H
