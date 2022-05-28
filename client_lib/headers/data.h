#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include "structures.h"

class Data{
    private:
        std::map<std::string, Chat> chats;
        std::map<std::string, std::vector<Message>> chat_messages;
    public:
        Chat getChat(std::string id);
        bool addChat(Chat);
        bool addMessages(Chat, std::vector<Message>);
        std::vector<Message> messagesFromChat(std::string chatId);
};

#endif