#include "middleware.h"
#include "server_address.h"

Middleware::Middleware(Client* c) : client(c) {
    net = NetModule::Create();
    net->Run(SERVER_IP, SERVER_PORT);
}

void Middleware::send(const std::string &chat_name, const std::string &text) {

}