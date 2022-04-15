#ifndef SERVER_REDBCONNECTION
#define SERVER_REDBCONNECTION

#include <map>

#include "DBRepo.h"
#include "User.h"
#include "ChatRoom.h"
#include "Message.h"

class DullConnection: iConnection{
    private:
        //no actual connection
    public:
        std::map<int, User> users;
        std::map<int, ChatRoom> chats;
        std::map<int, Message> messages;
        DullConnection(){};
        bool exec(Operation, std::vector<DBObject>);
        std::vector<DBObject> get(std::string);
};

#endif