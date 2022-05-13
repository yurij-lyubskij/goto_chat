//
// Created by yura11011 on 12.05.22.
//

#ifndef GOTO_CHAT_LISTENER_H
#define GOTO_CHAT_LISTENER_H

#include <utility>

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

    virtual void on_accept(std::error_code ec) = 0;
};

class Listener : public std::enable_shared_from_this<Listener>, public iListener {
    std::shared_ptr<iAcceptor> acceptor_;
    std::shared_ptr<iSocket> sock;
    std::shared_ptr<iRouter> router;

    static void fail(std::error_code ec, char const *what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }

public:


    Listener(
            std::shared_ptr<iSocket> sock,
            std::shared_ptr<iAcceptor> acceptor,
            std::shared_ptr<iRouter> router
    )
            : acceptor_(std::move(acceptor)), sock(std::move(sock)), router(std::move(router)) {
         std::error_code ec;
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
    void run() {
        do_accept();
    }

private:
    void
    do_accept() override {
        std::function lamda = [&](std::error_code ec) {
            if (!ec)
                on_accept(ec);
        };
        acceptor_->async_accept(sock, lamda);
    }

    void on_accept(std::error_code ec) override {
        if (ec) {
            fail(ec, "accept");
            return; // To avoid infinite loop
        } else {
            // Create the session and run it
            std::make_shared<UserSession>(sock, router)->start();
        }

        // Accept another connection
        do_accept();
    }
};


#endif //GOTO_CHAT_LISTENER_H
