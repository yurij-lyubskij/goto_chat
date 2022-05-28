#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

enum MessageType {text, voice};

struct Chat{
    std::string Id;
    std::string chatName;
};

struct Message{
    std::string Id;
    std::string text;
    std::string phone;
    std::string time;
    MessageType type;
};

class MessageComparator{
public:
    MessageComparator(){};
    bool operator()(const Message &first, const Message &second){
        return std::stoi(first.Id) < std::stoi(second.Id);
    };
};
#endif