//
// Created by yura11011 on 14.04.2022.
//

#include "Server.h"

void Server::Run() {

}

bool Server::Accept() {
    return false;
}

Request Server::ParseRequest(std::string) {
    return Request();
}

void Server::Route(Request) {

}

void Server::Send(Response) {

}

std::string Server::Serialise(Response) {
    return std::string();
}

Server::Server() {

}
