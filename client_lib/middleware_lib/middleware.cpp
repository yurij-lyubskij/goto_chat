#include "middleware.h"
#include "server_address.h"

Middleware::Middleware(Client *c) : client(c)
{
    par = new Parser(this);
    net = NetModule::Create();
    net->Run(SERVER_IP, SERVER_PORT);
}

Middleware::~Middleware()
{
    delete par;
}

void Middleware::send(const std::string &chat_name, const std::string &text)
{
    beast::http::request<beast::http::string_body> request = par->send_message(chat_name, text);
    net->Send(request);
}

bool registrate(const std::string &first_name, const std::string &second_name,
                const std::string &login, const std::string &password, const std::string &email)
{
}