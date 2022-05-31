// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_HANDLER_H
#define GOTO_CHAT_HANDLER_H


#include <memory>
#include <utility>
#include "Request.h"
#include "Response.h"
#include "AuthDb.h"
#include "UserRepo.h"
#include "jsonParser.h"

class iHandler {
public:
    virtual ~iHandler() = default;

    virtual bool CanHandle(Request) = 0;

    virtual Response Handle(Request) = 0;
};


class CreateNewUser : public iHandler {
    std::shared_ptr<iAuthDb> auth;
    std::shared_ptr<iUserRepo> users;
    std::shared_ptr<IjsonParser> parser;
public:
    CreateNewUser() = delete;

    explicit CreateNewUser(std::shared_ptr<iAuthDb> auth, std::shared_ptr<iUserRepo> user,
                           std::shared_ptr<IjsonParser> parser) : auth(std::move(auth)), users(std::move(user)),
                                                                  parser(std::move(parser)) {
    };

    bool CanHandle(Request) override;

    Response Handle(Request) override;
};

class Login : public iHandler {
    std::shared_ptr<iAuthDb> auth;
    std::shared_ptr<iUserRepo> users;
    std::shared_ptr<IjsonParser> parser;
public:
    explicit Login(std::shared_ptr<iAuthDb> auth, std::shared_ptr<iUserRepo> user,
                   std::shared_ptr<IjsonParser> parser) : auth(std::move(auth)), users(std::move(user)),
                                                          parser(std::move(parser)) {};

    Login() = delete;

    bool CanHandle(Request) override;

    Response Handle(Request) override;
};

class Logout : public iHandler {
    std::shared_ptr<iAuthDb> auth;
    std::shared_ptr<iUserRepo> users;
public:
    Logout() = delete;

    explicit Logout(std::shared_ptr<iAuthDb> auth, std::shared_ptr<iUserRepo> user) : auth(std::move(auth)),
                                                                                      users(std::move(user)) {};

    bool CanHandle(Request) override;

    Response Handle(Request) override;
};

class SendMessage : public iHandler {
public:
    explicit SendMessage(DBConnection<iConnection>* conn, std::shared_ptr<iAuthDb> auth): auth(auth), connections(conn) {};
    bool CanHandle(Request) override;

    Response Handle(Request) override;
private:
    std::shared_ptr<iAuthDb> auth;
    const std::string REQUESTED_TARGET = "/chat/message/send";
    DBConnection<iConnection>* connections;
};

class Example : public iHandler {
public:
    bool CanHandle(Request) override;

    Response Handle(Request) override;;
};

class GetVoice : public iHandler {
public:
    GetVoice(DBConnection<iConnection>* conn): connections(conn){};
    bool CanHandle(Request) override;

    Response Handle(Request) override;
private:
    DBConnection<iConnection>* connections;
    const std::string REQUESTED_TARGET = "/chat/message/getfile?name=";
};

class SendVoice : public iHandler {
public:
    SendVoice(DBConnection<iConnection>* conn, std::shared_ptr<iAuthDb> auth): auth(auth), connections(conn){};
    bool CanHandle(Request) override;

    Response Handle(Request) override;
private:
    std::shared_ptr<iAuthDb> auth;
    DBConnection<iConnection>* connections;
    const std::string REQUESTED_TARGET = "/chat/message/voice/send";
};

#endif //GOTO_CHAT_HANDLER_H
