#ifndef GOTO_CHAT_REQUEST_H
#define GOTO_CHAT_REQUEST_H

#include <vector>
#include <string>
#include <map>

#include "Response.h"

class Request {
public:
    std::vector<std::string> headers;
    std::string method;
    std::string cookie;
    std::string body;
    std::string URL;
    std::map<std::string, std::string> parameters;
    Response response;
};


#endif