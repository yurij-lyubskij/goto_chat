//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_ROUTER_H
#define GOTO_CHAT_ROUTER_H

#include <memory>
#include <vector>
#include "Handler.h"
#include "MiddleWare.h"
#include "Request.h"

class iRouter {
public:
    virtual ~iRouter() = default;
private:
    virtual void AddHandler(std::shared_ptr<iHandler>) = 0;
    virtual void RemoveHandler(std::shared_ptr<iHandler>) = 0;
    virtual void AddMiddle(std::shared_ptr<iMiddle>) = 0;
    virtual Request& UseMiddle(Request&) = 0;
    virtual bool SelectHandler(Request&) = 0;
    virtual void CallHandler(Request&) = 0;
};

class Router : public iRouter {
    Router();
    ~Router() = default;
private:
    void AddHandler(std::shared_ptr<iHandler>);
    void RemoveHandler(std::shared_ptr<iHandler>);
    void AddMiddle(std::shared_ptr<iMiddle>);
    Request& UseMiddle(Request&);
    bool SelectHandler(Request&);
    void CallHandler(Request&);

private:
    std::vector<std::shared_ptr<iHandler>> handlers;
    std::vector<std::shared_ptr<iMiddle>> middleware;

};


#endif //GOTO_CHAT_ROUTER_H
