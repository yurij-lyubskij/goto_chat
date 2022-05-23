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
    User user = auth->GetUser(req.cookie);
    Response response;
    auto userCheck =  users->GetbyId(user.Id);
    response.cookie = req.cookie;
    response.statusCode = OK;
    if (user.Name.empty() || (user.Name != userCheck.Name)){
        std::cout <<"result = "<< user.Name << "\n";
        response.statusCode = UnAuthorized;
    }
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

bool GetChatHistory::CanHandle(Request) {
    return false;
}

Response GetChatHistory::Handle(Request) {
    return Response();
}

bool CreateChatRoom::CanHandle(Request) {
    return false;
}

Response CreateChatRoom::Handle(Request) {
    return Response();
}

bool FindChatRoom::CanHandle(Request) {
    return false;
}

Response FindChatRoom::Handle(Request) {
    return Response();
}

bool JoiChatRoom::CanHandle(Request) {
    return false;
}

Response JoiChatRoom::Handle(Request) {
    return Response();
}

bool CreateNewUser::CanHandle(Request req) {
    return req.target == "/user/create";
}

Response CreateNewUser::Handle(Request req) {
    User user = parser->parseUser(req.body);
    Response response;
    auto userCheck =  users->GetbyName(user.Name);
    if (! userCheck.Name.empty()){
        response.statusCode = BadRequest;
        return response;
    }
    users->CreateUser(user);
    user = users->GetbyName(user.Name);
    response.cookie = auth->SetCookie(user) ;
    response.statusCode = OK;
    return response;
}

