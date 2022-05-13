//
// Created by yura11011 on 14.04.2022.
//

#include "AuthDb.h"
#include <ctime>
#include <iostream>
#include <unistd.h>

std::string gen_random(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

const int cookieLength = 255;

std::string AuthDb::SetCookie(std::string User) {
    srand((unsigned) time(NULL) * getpid());
    std::string NewCookie = gen_random(cookieLength);
    CookieMap[NewCookie] = User;
    return NewCookie;
}

std::string AuthDb::GetUser(std::string Cookie) {
   std::string User = "";
   User = CookieMap[Cookie];
   return User;
}

int AuthDb::DeleteCookie(std::string Cookie) {
    return CookieMap.erase(Cookie);
}