#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

struct Message{
    std::string text;
    std::string phone;
    std::string Id;
    std::string time;
};

struct Chat{
    std::string Id;
    std::string chatName;
};

#endif