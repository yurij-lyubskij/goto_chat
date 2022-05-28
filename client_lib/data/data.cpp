#include "data.h"

Chat Data::getChat(std::string id){
    if(!chats.contains(id)) return {"0", ""};
    return chats.at(id);
}

bool Data::addChat(Chat chat){
    if (chats.contains(chat.Id)) return false;
    chats.insert(std::make_pair(chat.Id, chat));
    chat_messages.insert(std::make_pair(chat.Id, std::vector<Message>()));
    return true;
};
bool Data::addMessages(Chat chat, std::vector<Message> messages){
    if (!chats.contains(chat.Id)) addChat(chat);
    std::vector<Message> allMessages = chat_messages.at(chat.Id);
    for (Message mes : messages)
        allMessages.push_back(mes);
    std::sort(allMessages.begin(), allMessages.end(), MessageComparator());
    std::map<std::string, std::vector<Message>>::iterator it = chat_messages.find(chat.Id); 
    if (it != chat_messages.end())
        it->second = allMessages;

};

std::vector<Message> Data::messagesFromChat(std::string chatId){
    if(!chat_messages.contains(chatId)) return std::vector<Message>();
    return chat_messages.at(chatId);
};