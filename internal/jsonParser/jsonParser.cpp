//
// Created by yura11011 on 14.05.22.
//

#include "jsonParser.h"
#include <ctime>
using namespace rapidjson;

const int saltLen = 25;

std::string genRandWithSeed(const int len,  std::string name) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    size_t seed = std::hash<std::string>{}(name);
    srand(seed);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

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
    if (d.HasMember("phone")) {
        user.PhoneNumber = d["phone"].GetString();
    }
    std::string salt = genRandWithSeed(saltLen, user.PhoneNumber);

    if (d.HasMember("password")) {
        std::string password = d["password"].GetString();
        password = password + salt;
        user.Hash = std::to_string(std::hash<std::string>{}(password));

    }
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

Message jsonParser::parseMSG(std::string body, int userid) {
    Document d;
    const char* json = body.c_str();
    d.Parse(json);
    time_t time = std::time(0);
    std::string content;
    std::string phone;
    if (d.HasMember("message")){
       if (d["message"].HasMember("userPhone")){
           phone = d["message"]["userPhone"].GetString();
       }
        if (d["message"].HasMember("userPhone")){
            content = d["message"]["text"].GetString();
        }
    }
    int chat = 0;
    if (d.HasMember("chatId")){
        chat = d["chatId"].GetInt();
    }
    Message msg(content, time, userid, chat);

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
