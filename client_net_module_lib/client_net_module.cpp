#include "client_net_module.h"

NetModule::NetModule() {}

void NetModule::Run() {}

void NetModule::Send() {}

int NetModule::Poll(std::string)
{
    return 2;
}

int NetModule::LongPoll(std::string)
{
    return 1;
}