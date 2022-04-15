#ifndef WEBSOCKET_SERVER
#define WEBSOCKET_SERVER

#include <stdlib.h>
#include <queue>
#include <memory>
#include <map>

#include "User.h"
#include "Message.h"

class WebSocketSession{
	public:
		void write();
		void read();
};

class WebSocketServer {
	private:
		std::map<int, WebSocketSession*> connections;
	public:
		std::queue<std::shared_ptr<Message>> m_pool;
		void addConnection(User);
		void removeConnection(User);
		void run();
};



#endif