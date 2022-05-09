#ifndef SERVER_REDBCONNECTION
#define SERVER_REDBCONNECTION

#include <map>
#include <gmock/gmock.h>
#include <vector>

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
        bool exec(DBRequest, std::vector<DBObject>);
        std::vector<DBObject> get(std::string);
};

class MockConnection: iConnection{
    public:
        MOCK_METHOD(bool, exec, (DBRequest, std::vector<DBObject>), (override));
        MOCK_METHOD(std::vector<DBObject>, get, (DBRequest), (override));
};

#endif