//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_RESPONSE_H
#define GOTO_CHAT_RESPONSE_H

#include <string>
#include <vector>

class Response {
private:
    std::vector<std::string> headers;
    std::string method;
    std::string body;
    std::string URL;
};


#endif //GOTO_CHAT_RESPONSE_H
