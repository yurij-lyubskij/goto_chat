#ifndef CLIENT_H
#define CLIENT_H

#include "httpClient.h"
#include "structures.h"

class Client
{
public:
    Client();
    ~Client() = default;

    void open_chat(const std::string &chat_name);

    Chat create_chat(std::vector<std::string> members, const std::string &chat_name);

    std::vector<Chat> find_chats(const std::string &chat_name);

    void delete_from_chat(const std::string &person_name);

    void leave_chat(const std::string &chat_name);

    void reload_chat(const std::string &login, const std::string &chat_name);

    void send_message(const std::string &chat_name, const std::string &text, const std::string &phone);

    bool person_exist(const std::string &login);

    bool registrate(const std::string &first_name, const std::string &second_name,
                    const std::string &login, const std::string &password, const std::string &email);

    void logout();

    bool sign_in(const std::string &phone, const std::string &password);

private:
    std::string cookie;
    net::io_context ioc;
};


#endif // CLIENT_H
