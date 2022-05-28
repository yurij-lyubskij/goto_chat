#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

enum MessageType {text, voice};

class MessageComparator{
public:
    MessageComparator(){};
    bool operator()(const Message &first, const Message &second){
        return std::stoi(first.Id) < std::stoi(second.Id);
    };
};

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

#endif