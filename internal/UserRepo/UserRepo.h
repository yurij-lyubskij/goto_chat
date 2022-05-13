//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_USERREPO_H
#define GOTO_CHAT_USERREPO_H

#include <map>
#include "User.h"
#include "DBRepo.h"


//Interface Block

class iUserRepo {
    DBConnection<iConnection> *connection;
public:
    virtual ~iUserRepo() = default;

    virtual bool CreateUser(User user) = 0;

    virtual bool UpdateUser(User user) = 0;

    virtual User GetbyId(size_t id) = 0;

    virtual std::vector<User> getManyByID(std::vector<size_t> id) = 0;

    virtual bool update(std::vector<User> users) = 0;

    virtual bool CreateMany(std::vector<User> users) = 0;
};


class UserRepo : public iUserRepo {
    DBConnection<iConnection> *connection;
    std::map<size_t, User> UserMap;
    size_t counter;
public:
    UserRepo(): counter(0){};
    bool CreateUser(User user) override;

    bool UpdateUser(User user) override;

    User GetbyId(size_t id) override;

    std::vector<User> getManyByID(std::vector<size_t> id) override;

    bool update(std::vector<User> users) override;

    bool CreateMany(std::vector<User> users) override;
};

#endif //GOTO_CHAT_USERREPO_H
