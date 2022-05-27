#ifndef BUILDER_H
#define BUILDER_H

#include <string>
//for messageListFromMes method
enum GetMessageMode {next, last};

class TargetBuilder{
public:
    static std::string findChat(const std::string& name);                                           // /chat/find/?name=name
    static std::string messageListFromEmptyChat(const std::string& chatId);                         // /chat/message/list/?chat=id
    static std::string messageListFromMes(const std::string& mesId, const GetMessageMode& mode);    // /chat/message/list/?mes=id&mode=(0,1)
    static std::string getUserChats(const std::string& phone);                                      // /user/getchat?user=phone
    static std::string createChat();                                                                // /chat/join/
    static std::string joinChat();                                                                  // /chat/join/
};

#endif