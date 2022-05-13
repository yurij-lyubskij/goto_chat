#ifndef SERVER_RECHATROOM
#define SERVER_RECHATROOM

#include <vector>
#include <gmock/gmock.h>
#include "ChatRoom.h"

class reChatRoom : public iChatRoom{
	public:
		MOCK_METHOD(bool, reactOn, (Message), (override));
};

#endif