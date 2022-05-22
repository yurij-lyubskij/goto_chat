//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_MIDDLEWARE_H
#define GOTO_CHAT_MIDDLEWARE_H

#include "Request.h"
#include <functional>
#include <memory>
#include <utility>

#include "AuthDb.h"

class iMiddle {
public:
    virtual ~iMiddle() = default;

    virtual Request& operator() (Request& request) = 0;
};

class CheckAuth : public iMiddle {
    std::shared_ptr<iAuthDb> auth;
public:
    explicit CheckAuth(std::shared_ptr<iAuthDb> auth): auth(std::move(auth)){};
    CheckAuth()= default;
    Request& operator() (Request& request) override;
};


#endif //GOTO_CHAT_MIDDLEWARE_H
