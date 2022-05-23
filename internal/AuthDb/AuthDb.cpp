//
// Created by yura11011 on 14.04.2022.
//

#include "AuthDb.h"
#include <ctime>
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

const int cookieLength = 25;

std::string AuthDb::SetCookie(User User) {
    srand((unsigned) time(NULL) * getpid());
    std::string NewCookie = gen_random(cookieLength);
    CookieMap[NewCookie] = User;
    return NewCookie;
}

User AuthDb::GetUser(std::string Cookie) {User user;
   user = CookieMap[Cookie];
   if (user.Name == "") {
       CookieMap.erase(Cookie);
   }
   return user;
}

int AuthDb::DeleteCookie(std::string Cookie) {
    auto deleted = CookieMap.erase(Cookie);
    return deleted;
}