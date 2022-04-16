#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
class Client
{
public:
    Client();
    void open_chat(const std::string &chat_name);
    void create_chat(const std::string &chat_name);

    void delete_from_chat(const std::string &person_name);
    void leave_chat(const std::string &chat_name);
    void reload_chat(const std::string &login, const std::string &chat_name);
    void send_message(const std::string &chat_name, const std::string &text);
    void registrate(const std::string &login, const std::string &password, const std::string &email);
    void logout(const std::string &user_name);
private:

};

#endif // CLIENT_H
