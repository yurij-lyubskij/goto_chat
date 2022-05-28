#ifndef WEBSOCKET_SERVER
#define WEBSOCKET_SERVER

#include <stdlib.h>
#include <queue>
#include <memory>
#include <map>

#include "User.h"
#include "Message.h"
#include "MessageQueue.h"

class WebSocketSession{
	public:
		void write();
		void read();
};

class iWebSocketServer {
	private:
		std::map<int, WebSocketSession*> connections;
		MessageQueue *queue;
	public:
		virtual void addToQueue(std::shared_ptr<iMessage>) = 0;
		virtual std::shared_ptr<iMessage> extractFromQueue() = 0;
		virtual void addConnection(User, WebSocketSession*) = 0;
		virtual void removeConnection(User) = 0;
		virtual void run() = 0;
};

class WebSocketServer: public iWebSocketServer{
	public:
		void addToQueue(std::shared_ptr<iMessage>);
		std::shared_ptr<iMessage> extractFromQueue();
		void addConnection(User, WebSocketSession*);
		void removeConnection(User);
		void run();
};

#endif