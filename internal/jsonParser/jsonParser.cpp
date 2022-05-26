//
// Created by yura11011 on 14.05.22.
//

#include "jsonParser.h"
#include <ctime>
using namespace rapidjson;

User jsonParser::parseUser(std::string body) {
//    std::cout << body <<"\n";

    Document d;
    const char* json = body.c_str();
    d.Parse(json);
    User user;
    user.Id = 0;
    user.Name = "";
    if (d.HasMember("username")){
        user.Name = d["username"].GetString();
    }
    user.PhoneNumber = d["phone"].GetString();
    user.password = d["password"].GetString();
    return user;
}

std::string jsonParser::serializeUser(User user) {
    std::string body;
    body += "{";
    body += "\"Id\":\"";
    body += std::to_string(user.Id);
    body += "\",";
    body += "\"Name\":\"";
    body += user.Name;
    body += "\",\"PhoneNumber\":\"";
    body += user.PhoneNumber;
    body += "\"}";
    return body;
}

Message jsonParser::parseMSG(std::string body) {
    Document d;
    const char* json = body.c_str();
    d.Parse(json);
    time_t time = std::time(0);
    std::string content;
    int sender = 0;
    if (d.HasMember("message")){
       if (d["message"].HasMember("userPhone")){
           sender = d["message"]["userPhone"].GetInt();
       }
        if (d["message"].HasMember("userPhone")){
            content = d["message"]["text"].GetString();
        }
    }

    int chat = 0;
    if (d.HasMember("chatId")){
        chat = d["chatId"].GetInt();
    }
    Message msg(content, time, sender, chat);

    return msg;
}

std::string jsonParser::serializeChat(const ChatRoom& chat) {
    std::string body;
    body += "{";
    body += "\"id\":\"";
    body += std::to_string(chat.getId());
    body += "\",";
    body += "\"chatName\":\"";
    body += chat.getName();
    body += "\"}";
    return body;
}

std::string jsonParser::serializeMessage(const iMessage& mes, const User& sender) {
    std::string body;
    body = "{";
    body += "\"id\":\"";
    body += std::to_string(mes.getId());
    body += "\",";
    body += "\"text\":\"";
    body += mes.getContent();
    body += "\",";
    body += "\"time\":\"";
    body += std::to_string(mes.getTime());
    body += "\",";
    body += "\"userPhone\":\"";
    body += sender.PhoneNumber;
    body += "\",";
    body += "\"type\":\"";
    body += (mes.getType() == textMessage)? "text" : "voice";
    body += "\"}";
    return body;
}
