//
// Created by yura11011 on 14.05.22.
//

#include "jsonParser.h"
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
