#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "middleware.h"

class Middleware;

class Client
{
public:
    Client();
    ~Client();

    static void open_chat(const std::string &chat_name);

    static void create_chat(const std::string &owner, const std::string &chat_name);

    static void delete_from_chat(const std::string &person_name);

    static void leave_chat(const std::string &chat_name);

    static void reload_chat(const std::string &login, const std::string &chat_name);

    void send_message(const std::string &chat_name, const std::string &text);

    static bool person_exist(const std::string &login);

    static bool registrate(const std::string &first_name, const std::string &second_name,
                           const std::string &login, const std::string &password, const std::string &email);

    static void logout(const std::string &user_name);

    static bool sign_in(const std::string &login, const std::string &password);

private:
    Middleware *mid;
};

#endif // CLIENT_H
