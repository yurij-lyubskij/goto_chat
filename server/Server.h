//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_SERVER_H
#define GOTO_CHAT_SERVER_H

#include <utility>

#include "Router.h"
#include "Request.h"

class iServer {
public:
    virtual ~iServer() = default;

    virtual void Run() = 0;

private:
    virtual bool Accept() = 0;

    virtual Request ParseRequest(std::string) = 0;

    virtual void Route(Request) = 0;

    virtual void Send(Response) = 0;

    virtual std::string Serialise(Response) = 0;
};

class iContext {
public:
    virtual void run() = 0;
};

typedef std::shared_ptr<iContext> context;

class Server : public iServer {
public:
    explicit Server(context ioc): _ioc(std::move(ioc)) {};

    void Run() override;

    Request ParseRequest(std::string) override;

    std::string Serialise(Response) override;

    void Route(Request) override;

    void Send(Response) override;

private:
    context _ioc;
    bool Accept() override;
};

#endif //GOTO_CHAT_SERVER_H
