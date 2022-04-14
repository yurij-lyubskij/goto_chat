//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_REQUEST_H
#define GOTO_CHAT_REQUEST_H

#include "Response.h"


class Request {
public:
    UserSession session;
    std::vector<std::string> headers;
    std::string method;
    std::string cookie;
    std::string body;
    std::string URL;
    Response response;

};


#endif //GOTO_CHAT_REQUEST_H
