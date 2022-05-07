#include "Message.h"

Message::Message(const Message& mes){
	id = mes.id;
	senderId = mes.senderId;
	sendTime = mes.sendTime;
	content = mes.content;
};

Message Message::operator=(const Message& mes){
	return Message(mes);
}