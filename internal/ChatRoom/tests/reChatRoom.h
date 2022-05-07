#ifndef SERVER_RECHATROOM
#define SERVER_RECHATROOM

#include <vector>
#include <gmock/gmock.h>
#include "ChatRoom.h"

class reChatRoom : public iChatRoom{
	public:
		//MOCK_METHOD(bool, addUser, (User), (override));
		//MOCK_METHOD(bool, removeUser, (User), (override));
		MOCK_METHOD(bool, reactOn, (Message), (override));
		MOCK_METHOD(std::vector<User>, getMembers, (), (override));
};

#endif