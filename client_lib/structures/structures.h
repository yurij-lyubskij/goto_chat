#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

enum MessageType {text, voice};

struct Message{
    std::string Id;
    std::string text;
    std::string phone;
    std::string time;
    MessageType type;
};

struct Chat{
    std::string Id;
    std::string chatName;
};

struct User {
    std::string username;
    std::string phone;
    std::string password;
};

#endif