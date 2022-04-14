//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_SERVER_H
#define GOTO_CHAT_SERVER_H

#include "Router.h"
#include "Request.h"

class iServer {
public:
    virtual ~iServer() = default;
    virtual void Run() = 0;
private:
    virtual bool Accept() = 0;
    virtual Request ParseRequest() = 0;
    virtual void Route(Request) = 0;
    virtual void Send(Response) = 0;
    virtual std::string Serialise(Response) = 0;
};

class Server : public iServer {
public:
   Server();
   void Run() override;
private:
    bool Accept() override;
    Request ParseRequest() override;
    void Route(Request) override;
    void Send(Response) override;
    std::string Serialise(Response) override;
};

#endif //GOTO_CHAT_SERVER_H
