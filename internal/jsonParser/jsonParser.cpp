//
// Created by yura11011 on 14.05.22.
//

#include "jsonParser.h"

User jsonParser::parseUser(std::string body) {
    User user;
    user.Id = 1;
    user.Name = body;
    user.PhoneNumber = body;
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
