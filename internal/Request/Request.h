//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_REQUEST_H
#define GOTO_CHAT_REQUEST_H

#include "Response.h"

class Request {
private:
    std::vector<std::string> headers;
    std::string method;
    std::string body;
    std::string URL;
    Response response;
//    UserSession session;
};


#endif //GOTO_CHAT_REQUEST_H
