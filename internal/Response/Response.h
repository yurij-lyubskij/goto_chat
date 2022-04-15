#ifndef GOTO_CHAT_RESPONSE_H
#define GOTO_CHAT_RESPONSE_H

#include <vector>
#include <string>

class Response{
public:
	Response(){};
    std::vector<std::string> headers;
    std::string cookie;
    std::string method;
    std::string body;
    int statusCode;
};


#endif 