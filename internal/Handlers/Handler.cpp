#include <iostream>
#include "Handler.h"

//
// Created by yura11011 on 14.04.2022.
//

#include "Handler.h"

bool Login::CanHandle(Request req) {
    return req.target == "/session/create";
}

Response Login::Handle(Request req) {
    User user = parser->parseUser(req.body);
    Response response;
    auto userCheck =  users->GetbyPhone(user.PhoneNumber);
    if (userCheck.Name.empty() || (user.password!= userCheck.password)){
        response.statusCode = NotFound;  //User Not Found
        return response;
    }
    response.cookie = auth->SetCookie(userCheck) ;
    response.statusCode = OK;
//    response.body = "json here sometimes";
    return response;
}


bool Logout::CanHandle(Request req) {
    return req.target == "/session/delete";
}

Response Logout::Handle(Request req) {
    int deleted = auth->DeleteCookie(req.cookie);
    Response response;
    response.cookie = "";
    response.statusCode = OK;
    if (deleted == 0) {
        response.statusCode = NotFound;
    }
    return response;
}

bool SendMessage::CanHandle(Request) {
    return false;
}

Response SendMessage::Handle(Request) {
    return Response();
}

bool CreateNewUser::CanHandle(Request req) {
    return req.target == "/user/create";
}

Response CreateNewUser::Handle(Request req) {
    User user = parser->parseUser(req.body);
    Response response;
    auto userCheck =  users->GetbyPhone(user.PhoneNumber);
    if (! userCheck.Name.empty()){
        response.statusCode = BadRequest;
        return response;
    }
    users->CreateUser(user);
    user = users->GetbyPhone(user.PhoneNumber);
    response.cookie = auth->SetCookie(user) ;
    response.statusCode = OK;
    return response;
}

bool Example::CanHandle(Request req) {
    return req.target == "/user/example";
}

Response Example::Handle(Request req) {
    Response response;
    response.statusCode = OK;
    if (req.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    return response;
}
