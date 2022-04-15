//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_RESPONSE_H
#define GOTO_CHAT_RESPONSE_H

#include <string>
#include <vector>
#include "UserSession.h"

class Response {
public:
    UserSession session;
    std::vector<std::string> headers;
    std::string cookie;
    std::string body;
    int statusCode;
};

#endif //GOTO_CHAT_RESPONSE_H