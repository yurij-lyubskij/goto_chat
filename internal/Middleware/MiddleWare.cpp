//
// Created by yura11011 on 14.04.2022.
//

#include "MiddleWare.h"

Request &CheckAuth::operator()(Request &request) {
    std::string cookie = request.cookie;
    std::string user = auth->GetUser(cookie);
    if (user.empty()) {
        request.responseStatus = UnAuthorized;
    }
    return request;
}
