//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_AUTHDB_H
#define GOTO_CHAT_AUTHDB_H


#include <string>

class iAuthDb {
public:
    virtual ~iAuthDb() = default;

    virtual std::string GetCookie(std::string Id) = 0;

    virtual std::string SetCookie(std::string Id) = 0;
};

class AuthDb : public iAuthDb {
public:
    std::string GetCookie(std::string Id) override;

    std::string SetCookie(std::string Id) override;
};

#endif //GOTO_CHAT_AUTHDB_H
