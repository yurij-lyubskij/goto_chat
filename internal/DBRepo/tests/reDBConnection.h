#ifndef SERVER_REDBCONNECTION
#define SERVER_REDBCONNECTION

#include <map>
#include <gmock/gmock.h>
#include <vector>
#include <list>

#include "DBRepo.h"
#include "User.h"
#include "ChatRoom.h"
#include "Message.h"
/*
class DullConnection: iConnection{
    private:
        //no actual connection
    public:
        std::map<int, User> users;
        std::map<int, ChatRoom> chats;
        std::map<int, Message> messages;
        DullConnection(){};
        bool exec(DBRequest, std::vector<DBObject>) override;
        std::vector<DBObject> get(std::string) override;
};
*/
class MockConnection: public iConnection{
    public:
        int usersCount = 0;
        std::map<int, User> users;
        std::map<std::string, User> userByPhone;
        int chatsCount = 0;
        std::map<int, ChatRoom> chats;
        int mesCount = 0;
        std::map<int, iMessage> messages;
        std::map<int, int> users_chats;
        std::map<int, std::vector<int>> chats_messages;
        MOCK_METHOD(bool, reExec, (DBRequest, std::vector<DBObject>), ());
        MOCK_METHOD(std::vector<DBObject>, reGet, (DBRequest), ());
    private:
        std::vector<DBObject> exec(DBRequest, std::vector<DBObject>) override;
        std::vector<DBObject> get(DBRequest) override;
};

#endif