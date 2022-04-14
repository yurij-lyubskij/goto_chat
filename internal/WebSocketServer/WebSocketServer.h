#ifndef WEBSOCKET_SERVER
#define WEBSOCKET_SERVER

#include <stdlib.h>

class WebSocketServer {
public:
	std::queue<std::shared_ptr<iConnection>> que;
    void run();
};

#endif