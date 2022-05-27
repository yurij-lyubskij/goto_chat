#include <boost/algorithm/string/predicate.hpp>
#include "httpBuffer.h"
#include "Handler.h"
#include <fstream>
#include <iostream>

//
// Created by yura11011 on 14.04.2022.
//

#include "Handler.h"
const std::string staticPath = "/home/yura11011/goto_chat/static/";

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

bool SendMessage::CanHandle(Request req ) {
    return  req.target == REQUESTED_TARGET;
}

Response SendMessage::Handle(Request req) {
    Response response;
    response.statusCode = OK;
    if (req.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    MessageRepo repo(connections);
    jsonParser parser;
    User user = auth->GetUser(req.cookie);
    int userid = user.Id;
    Message msg = parser.parseMSG(req.body, userid);

    std::vector<iMessage> message;
    message.push_back(msg);
    std::vector<int> ids = repo.put(message);
    if (ids.empty()) {
        response.statusCode = BadRequest;
    }
    return response;
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
    bool success = users->CreateUser(user);
    if (!success){
        response.statusCode = BadRequest;
        return response;
    }
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

bool GetVoice::CanHandle(Request request) {
    return boost::starts_with(request.target, REQUESTED_TARGET);
}

Response GetVoice::Handle(Request request) {
    Response response;

    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = OK;
    response.isFile = true;
    std::string fileName  = request.target.substr(REQUESTED_TARGET.size(), request.target.size() - 1);
    fileName  = staticPath + fileName;
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(fileName.c_str(), beast::file_mode::scan, ec);
    // Handle the case where the file doesn't exist
    if(ec == beast::errc::no_such_file_or_directory || !body.is_open()) {
        response.statusCode = NotFound;
        return response;
    }
    response.file_body = std::move(body);
    return response;
}

bool SendVoice::CanHandle(Request request) {
    return  boost::starts_with(request.target, REQUESTED_TARGET);
}

Response SendVoice::Handle(Request req) {
    Response response;
    if (req.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    size_t  size = req.body.size();
    int pos = req.body.find("Content-Type:");
    if (pos > 0) {
        req.body.erase(0, pos);
    }
    pos = req.body.find("\n");
    req.body.erase(0, pos);
    size = req.body.size();
    time_t time = std::time(0);
    std::string fName = req.headers[0];
    int chat = stoi(req.headers[1]);
    User user = auth->GetUser(req.cookie);
    VoiceMessage msg(fName, time, user.Id, chat);
    std::vector<iMessage> message;
    message.push_back(msg);
    MessageRepo repo(connections);
    std::vector<int> ids = repo.put(message);
    if (ids.empty()) {
        response.statusCode = BadRequest;
    }
    std::string fileName = staticPath + fName;
    std::ofstream fout(fileName, std::ios::binary);
    fout.write(req.body.c_str(), req.body.size());
    fout.close();
    response.statusCode = OK;
    return response;
}
