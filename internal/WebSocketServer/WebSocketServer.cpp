#include "WebSocketServer.h"

void WebSocketServer::addToQueue(std::shared_ptr<iMessage>) {

}

std::shared_ptr<iMessage> WebSocketServer::extractFromQueue() {
    return std::shared_ptr<iMessage>();
}

void WebSocketServer::addConnection(User, WebSocketSession *) {

}

void WebSocketServer::removeConnection(User) {

}

void WebSocketServer::run() {

}
