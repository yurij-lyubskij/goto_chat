#include "Message.h"

Message::Message(){ 
	id = -1;
	content = "";
	sendTime = 0;
	senderId = 0;
};

Message::Message(int _id) { 
	id = _id;
	content = "";
	sendTime = 0;
	senderId = 0;
};

Message::Message(std::string _content, time_t time, int sender){
	id = 0;
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