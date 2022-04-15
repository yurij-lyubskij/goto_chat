//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_USERSESSION_H
#define GOTO_CHAT_USERSESSION_H

#include <string>

class iUserSession {
public:
    virtual ~iUserSession() = default;
private:
    virtual std::string Read() = 0;
    virtual void Write(std::string) = 0;
};

//typedef Socket ip::tcp::socket sock;
class Socket{};

class UserSession : public iUserSession {
public:
    std::string Read() override;
    void Write(std::string) override;
private:
    Socket socket;
};

#endif //GOTO_CHAT_USERSESSION_H
