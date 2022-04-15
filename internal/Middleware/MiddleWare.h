//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_MIDDLEWARE_H
#define GOTO_CHAT_MIDDLEWARE_H

#include "Request.h"
#include <functional>
#include <memory>
class iMiddle {
public:
    virtual ~iMiddle() = default;

    virtual Request& operator() (Request& request, std::function<iMiddle> callback()) = 0;
};

class CheckAuth : public iMiddle {
public:
    Request& operator() (Request& request, std::function<iMiddle> callback()) override;
};


#endif //GOTO_CHAT_MIDDLEWARE_H
