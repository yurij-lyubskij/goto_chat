//
// Created by yura11011 on 14.04.2022.
//

#include "Router.h"

void Router::AddHandler(std::shared_ptr<iHandler>){};
void Router::RemoveHandler(std::shared_ptr<iHandler>){};
void Router::AddMiddle(std::shared_ptr<iMiddle>){};
void Router::UseMiddle(){};
bool Router::SelectHandler(){
    return false;
};
void Router::CallHandler() {};