//
// Created by yura11011 on 14.04.2022.
//

#include "Router.h"

const int16_t notFound = 404;

void Router::AddHandler(std::shared_ptr<iHandler> handler) {
    handlers.emplace_back(handler);
};

void Router::AddMiddle(std::shared_ptr<iMiddle> middle) {
    middleware.emplace_back(middle);
};

Request &Router::UseMiddle(Request &request) {
    std::shared_ptr<iMiddle> prev;
    for (auto& middle : middleware) {
        request = (*middle)(request);
        if (request.responseStatus != OK) {
            break;
        }
    }
    
    return request;
}

Response Router::Route(Request & req) {
    for (const auto& handler : handlers) {
        if (handler->CanHandle(req)) {
            return handler->Handle(req);
        }
    }
    Response res;
    res.statusCode = notFound;
    return res;
};
