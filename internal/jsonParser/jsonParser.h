//
// Created by yura11011 on 14.05.22.
//

#ifndef GOTO_CHAT_JSONPARSER_H
#define GOTO_CHAT_JSONPARSER_H
#include "User.h"
#include <iostream>

#include "rapidjson/writer.h"

#include "rapidjson/document.h"

#include "rapidjson/stringbuffer.h"
#include "Message.h"

class IjsonParser {
public:
    virtual ~IjsonParser() = default;
    virtual User parseUser (std::string body) = 0;
    virtual Message parseMSG (std::string body, int userid) = 0;
    virtual std::string serializeUser (User user) = 0;
};

class jsonParser: public IjsonParser {
public:
    User parseUser (std::string body) override;
    Message parseMSG (std::string body, int userid) override;
    std::string serializeUser (User user) override;
};

#endif //GOTO_CHAT_JSONPARSER_H
