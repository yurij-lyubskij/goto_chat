#include "MessageQueue.h"

void MessageQueue::Push(std::shared_ptr<iMessage> mes){
	messages.push(mes);
};

std::shared_ptr<iMessage> MessageQueue::Pop(){
	std::shared_ptr<iMessage> message = messages.front();
	messages.pop();
	return message;
};