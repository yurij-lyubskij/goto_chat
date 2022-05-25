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
    virtual bool CreateMany(std::vector<User> users) = 0;

    virtual User GetbyId(size_t id) = 0;
    virtual std::vector<User> getManyByID(std::vector<size_t> id) = 0;

    virtual User GetbyPhone(std::string Phone) = 0;
    virtual std::vector<User> GetManybyPhone(std::vector<std::string> phone)  = 0;
};


class UserRepo : public iUserRepo {
    DBConnection<iConnection>* connection;
    const std::string REQUESTED_TARGET = "/chat/create";
public:
    explicit UserRepo(DBConnection<iConnection>* conn): connection(conn){};

    bool CreateUser(User user) override;
    bool CreateMany(std::vector<User> users) override;

    User GetbyId(size_t id) override;
    std::vector<User> getManyByID(std::vector<size_t> id) override;

    User GetbyPhone(std::string Phone) override;
    std::vector<User> GetManybyPhone(std::vector<std::string> phone) override;

};

#endif //GOTO_CHAT_USERREPO_H
