//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_AUTHDB_H
#define GOTO_CHAT_AUTHDB_H


#include <string>
#include <map>
#include <User.h>

class iAuthDb {
public:
    virtual ~iAuthDb() = default;

    virtual User GetUser(std::string Cookie) = 0;

    virtual int DeleteCookie(std::string Cookie) = 0;

    virtual std::string SetCookie(User User) = 0;


};

class AuthDb : public iAuthDb {

    std::map<std::string, User> CookieMap;

public:

    User GetUser(std::string Cookie) override;

    int DeleteCookie(std::string Cookie) override;

    std::string SetCookie(User User) override;
};

#endif //GOTO_CHAT_AUTHDB_H
