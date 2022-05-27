#include <string>

#include "targetBuilder.h"

// /chat/find/?name=name
std::string TargetBuilder::findChat(const std::string& name){
    return ("/chat/find/?name=" + name);
};

// /chat/message/list/?chat=id                    
std::string TargetBuilder::messageListFromEmptyChat(const std::string& chatId){
    return ("/chat/message/list/?chat=" + chatId);
};

// /chat/message/list/?mes=id&mode=(0,1)
std::string TargetBuilder::messageListFromMes(const std::string& mesId, const GetMessageMode& mode){
    return ("/chat/message/list/?mes=" + mesId + "&mode=" + std::to_string(mode));
};      
// /user/getchat/?user=phone
std::string TargetBuilder::getUserChats(const std::string& phone){
    return ("/user/getchat/?user=" + phone);
};

std::string TargetBuilder::createChat() {return "/chat/create";};
std::string TargetBuilder::joinChat() {return "/chat/join";};