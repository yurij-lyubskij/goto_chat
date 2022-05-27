#include <string>

#include "targetBuilder.h"

// /chat/find/?name=name
std::string TargetBuilder::findChat(const std::string& name){
    return ("/chat/find/?name=" + name);
};

// /chat/message/list/?chat=id                    
std::string messageListFromEmptyChat(const int& chatId){
    return ("/chat/message/list/?chat=" + std::to_string(chatId));
};

// /chat/message/list/?mes=id&mode=(0,1)
std::string messageListFromMes(const int& mesId, const GetMessageMode& mode){
    return ("/chat/message/list/?chat=" + std::to_string(mesId) + "&mode=" + std::to_string(mode));
};      
// /user/getchat/?user=phone
std::string getUserChats(const std::string& phone){
    return ("/user/getchat/?user=" + phone);
};