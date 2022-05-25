#include "client.h"
#include "client_net_module.h"
#include "parser.h"

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

class Client;
class Parser;

class Middleware
{
public:
    Middleware(Client *c);
    ~Middleware();

    void send(const std::string &chat_name, const std::string &text);
    void open_chat(const std::string &chat_name);

    void create_chat(const std::string &owner, const std::string &chat_name);

    void delete_from_chat(const std::string &person_name);

    void leave_chat(const std::string &chat_name);

    void reload_chat(const std::string &login, const std::string &chat_name);

    bool person_exist(const std::string &login);

    bool registrate(const std::string &first_name, const std::string &second_name,
                    const std::string &login, const std::string &password, const std::string &email);

    void logout(const std::string &user_name);

    bool sign_in(const std::string &login, const std::string &password);

private:
    Client *client;
    std::shared_ptr<NetModule> net;
    Parser *par;
};

#endif