//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_CONTEXT_H
#define GOTO_CHAT_CONTEXT_H
#include "Acceptor.h"

class iContext {
public:
    virtual void run() = 0;
};

class Context : public iContext {
public:
    Context(net::io_context &ioc) : ioc(ioc) {};

    void run() override {
        ioc.run();
    };
private:
    net::io_context &ioc;
};



#endif //GOTO_CHAT_CONTEXT_H
