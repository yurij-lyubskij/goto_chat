//
// Created by yura11011 on 14.04.2022.
//

#include "MiddleWare.h"

Request &CheckAuth::operator()(Request &request, std::function<iMiddle> callback()) {
    return request;
}
