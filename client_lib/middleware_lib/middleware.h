#include "client.h"
#include "client_net_module.h"

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

class Client;

class Middleware
{
public:
    Middleware(Client *c);
    ~Middleware();

    void send(const std::string &chat_name, const std::string &text);

private:
    Client *client;
    std::shared_ptr<NetModule> net;
};

#endif