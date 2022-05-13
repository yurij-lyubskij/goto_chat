//
// Created by yura11011 on 14.04.2022.
//

#include "Router.h"

void Router::AddHandler(std::shared_ptr<iHandler> handler) {
    handlers.emplace_back(handler);
};

void Router::AddMiddle(std::shared_ptr<iMiddle> middle) {
    middleware.emplace_back(middle);
};

Request &Router::UseMiddle(Request &request) {
    return request;
};

bool Router::SelectHandler(Request &) {
    return false;
};

Response Router::CallHandler(Request &) {
    return Response();
};