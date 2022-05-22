//
// Created by yura11011 on 14.04.2022.
//

#include "MiddleWare.h"

Request &CheckAuth::operator()(Request &request) {
    std::string cookie = request.cookie;
    User user;
    if (!request.cookie.empty()) {
        user = auth->GetUser(cookie);
    }
    if (request.cookie.empty()|| user.Name.empty()) {
        request.responseStatus = UnAuthorized;
    }
    return request;
}
