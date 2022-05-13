//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_AUTHDB_H
#define GOTO_CHAT_AUTHDB_H


#include <string>
#include <map>

class iAuthDb {
public:
    virtual ~iAuthDb() = default;

    virtual std::string GetUser(std::string Cookie) = 0;

    virtual int DeleteCookie(std::string Cookie) = 0;

    virtual std::string SetCookie(std::string User) = 0;


};

class AuthDb : public iAuthDb {

    std::map<std::string, std::string> CookieMap;

public:

    std::string GetUser(std::string Cookie) override = 0;

    int DeleteCookie(std::string Cookie) override = 0;

    std::string SetCookie(std::string User) override;
};

#endif //GOTO_CHAT_AUTHDB_H
