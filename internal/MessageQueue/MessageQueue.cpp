#include "MessageQueue.h"

void MessageQueue::push(std::shared_ptr<iMessage> mes){
	messages.push(mes);
};

std::shared_ptr<iMessage> MessageQueue::pop(){
	std::shared_ptr<iMessage> message = messages.front();
	messages.pop();
	return message;
};
