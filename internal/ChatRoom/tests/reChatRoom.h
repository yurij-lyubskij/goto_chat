#ifndef SERVER_RECHATROOM
#define SERVER_RECHATROOM

#include "server.h"

class reChatRoom : public iChatRoom{
	MOCK_METHOD(bool, addUser, (User), (override));
	MOCK_METHOD(bool, removeUser, (User), (override));
	MOCK_METHOD(bool, reactOn, (User), (override));
	MOCK_METHOD(bool, addUser, (), (override));
}

#endif