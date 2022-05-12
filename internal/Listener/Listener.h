//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_LISTENER_H
#define GOTO_CHAT_LISTENER_H

#include "Acceptor.h"
#include "UserSession.h"

class iListener {
public:
    iListener() = default;

    // Start accepting incoming connections
    virtual void run() = 0;

    virtual ~iListener() = default;

private:
    virtual void do_accept() = 0;

    virtual void on_accept(beast::error_code ec, tcp::socket socket) = 0;
};

class Listener : public std::enable_shared_from_this<Listener>, public iListener {
    net::io_context &ioc_;
    std::shared_ptr<iAcceptor> acceptor_;
    static void fail(beast::error_code ec, char const *what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }
public:



    Listener(
            net::io_context &ioc,
            std::shared_ptr<iAcceptor> &acceptor
    )
            : ioc_(ioc), acceptor_(acceptor){
        beast::error_code ec;

        // Open the acceptor
        acceptor_->open(ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_->set_option(true, ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_->bind(ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_->listen(ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run() {
        do_accept();
    }

private:
    void
    do_accept() override {
        tcp::socket socket{ioc_};
        std::function lamda  = [&](beast::error_code ec)
        {
            if(!ec)
                on_accept(ec, std::move(socket));
        };
        acceptor_->async_accept(socket, lamda);
    }

    void on_accept(beast::error_code ec, tcp::socket socket) override {
        if (ec) {
            fail(ec, "accept");
            return; // To avoid infinite loop
        } else {
            // Create the session and run it
            std::make_shared<UserSession>(std::move(socket))->start();
        }

        // Accept another connection
        do_accept();
    }
};


#endif //GOTO_CHAT_LISTENER_H
