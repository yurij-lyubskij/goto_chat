#include "Message.h"

Message::Message(){ id = 0; };

Message::Message(int _id) { id = _id; };

Message::Message(std::string _content, time_t time, int sender){
	content = _content;
	sendTime = time;
	senderId = sender;
};

Message::Message(int _id, std::string _content, time_t time, int sender){
	id = _id;
	content = _content;
	sendTime = time;
	senderId = sender;
};

Message::Message(const Message& mes){
	id = mes.id;
	senderId = mes.senderId;
	sendTime = mes.sendTime;
	content = mes.content;
};

Message Message::operator=(const Message& mes){
	return Message(mes);
}