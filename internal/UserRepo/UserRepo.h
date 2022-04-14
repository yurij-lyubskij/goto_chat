//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_USERREPO_H
#define GOTO_CHAT_USERREPO_H

#include "User.h"

class iUserRepo {
public:
    virtual ~iUserRepo() = default;

    virtual size_t CreateUser(User user) = 0;

    virtual User GetbyId(size_t id) = 0;
};

class UserRepo : public iUserRepo {
public:
    size_t CreateUser(User user) override;

    User GetbyId(size_t id) override;
};

#endif //GOTO_CHAT_USERREPO_H
