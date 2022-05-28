//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_RESPONSE_H
#define GOTO_CHAT_RESPONSE_H

#include <string>
#include <thread>
#include <vector>

class Response {
public:
    Response():isFile(false) {};
    std::vector<std::string> headers;
    bool isFile;
    std::string cookie;
    std::string body;
    int statusCode;
};

#endif //GOTO_CHAT_RESPONSE_H

