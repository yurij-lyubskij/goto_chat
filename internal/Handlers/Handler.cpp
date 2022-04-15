//
// Created by yura11011 on 14.04.2022.
//

#include "Handler.h"


bool Login::CanHandle(Request) {
    return false;
}

Response Login::Handle(Request) {
    return Response();
}

bool Logout::CanHandle(Request) {
    return false;
}

Response Logout::Handle(Request) {
    return Response();
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

bool CreateNewUser::CanHandle(Request) {
    return false;
}

Response CreateNewUser::Handle(Request) {
    return Response();
}
