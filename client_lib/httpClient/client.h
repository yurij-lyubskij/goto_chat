#ifndef CLIENT_H
#define CLIENT_H

#include "httpClient.h"
#include "structures.h"

class Client
{
public:
    Client();
    ~Client() = default;


    Chat create_chat(const std::string &chat_name, std::vector<std::string> members);
    bool join_chat(const std::string &chatId, const std::string &phone);
    std::vector<Chat> find_chats(const std::string &chat_name);
    std::vector<Chat> get_users_chats(const std::string &chat_name);

    std::vector<Message> get_next_messages(const std::string &mes_id);
    std::vector<Message> get_last_messages(const std::string &mes_id);
    std::vector<Message> get_last_chat_messages(const std::string &chat_id);

    bool registerUser(const std::string &username, const std::string &phone, const std::string &password);

    void logout();
    bool getVoice (const std::string &name);
    bool sendVoice (const std::string &name, const std::string& chatid);
    bool sign_in(const std::string &phone, const std::string &password);

private:
    std::string cookie;
    net::io_context ioc;
};


#endif // CLIENT_H
