// Created by RIskhakov1

#include <string>

#ifndef CLIENT_NET_MODULE_H
#define CLIENT_NET_MODULE_H

class NetModule
{
public:
    NetModule();

    void Run();

    void Send();

    int Poll(std::string);

    int LongPoll(std::string);
};

#endif