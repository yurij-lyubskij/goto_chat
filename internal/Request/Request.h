//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_REQUEST_H
#define GOTO_CHAT_REQUEST_H

#include <map>
#include <vector>

const int16_t OK = 200;

class Request {
public:
    Request() {
        responseStatus = OK;
    }

    std::vector<std::string> headers;
    std::string method;
    std::string cookie;
    std::string body;
    std::string target;
    int16_t responseStatus;
    std::map<std::string, std::string> parameters;
};


#endif //GOTO_CHAT_REQUEST_H
