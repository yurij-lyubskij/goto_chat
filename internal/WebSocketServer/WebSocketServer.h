#ifndef WEBSOCKET_SERVER
#define WEBSOCKET_SERVER

#include <stdlib.h>
#include <queue>
#include <memory>

class WebSocketServer {
public:
	//std::queue<std::shared_ptr<iConnection>> que;
    void run();
};

#endif