#ifndef REWEBSOCKET_SERVER
#define REWEBSOCKET_SERVER

#include <gmock/gmock.h>
#include "WebSocketServer.h"
#include "Message.h"

class reWebSocketServer: public iWebSocketServer{
	public:
		MOCK_METHOD(void, addToQueue, (std::shared_ptr<iMessage>), (override));
		MOCK_METHOD(std::shared_ptr<iMessage>, extractFromQueue, (), (override));
		MOCK_METHOD(void, addConnection, (User, WebSocketSession*), (override));
		MOCK_METHOD(void, removeConnection, (User), (override));
		MOCK_METHOD(void, run, (), (override));
};

#endif