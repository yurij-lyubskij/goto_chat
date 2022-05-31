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
};

class iWebSocketServer {
	public:
        virtual ~iWebSocketServer() = default;
		virtual void addToQueue(std::shared_ptr<iMessage>) = 0;
		virtual std::shared_ptr<iMessage> extractFromQueue() = 0;
		virtual void addConnection(User, WebSocketSession*) = 0;
		virtual void removeConnection(User) = 0;
		virtual void run() = 0;
};

class WebSocketServer: public iWebSocketServer{
private:
    std::map<int, WebSocketSession*> connections;
    MessageQueue *queue;
	public:
        WebSocketServer() = default;
		void addToQueue(std::shared_ptr<iMessage>) override;
		std::shared_ptr<iMessage> extractFromQueue() override;
		void addConnection(User, WebSocketSession*) override;
		void removeConnection(User) override;
		void run() override;
};

#endif