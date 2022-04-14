//
// Created by yura11011 on 14.04.2022.
//

#include "Router.h"

void Router::AddHandler(std::shared_ptr<iHandler>) {

};

void Router::RemoveHandler(std::shared_ptr<iHandler>) {

};

void Router::AddMiddle(std::shared_ptr<iMiddle>) {

};

Request &Router::UseMiddle(Request & request) {
    return request;
};

bool Router::SelectHandler(Request &) {
    return false;
};

Response Router::CallHandler(Request &) {};