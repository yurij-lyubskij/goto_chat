#include "Message.h"

//
//(Text)Message section
//

Message::Message(){ 
	id = -1;
	content = "";
	sendTime = 0;
	senderId = 0;
	type = text;
};

Message::Message(int _id) { 
	id = _id;
	content = "";
	sendTime = 0;
	senderId = 0;
	type = text;
};

Message::Message(std::string _content, time_t time, int sender){
	id = 0;
	content = _content;
	sendTime = time;
	senderId = sender;
	type = text;
};

Message::Message(int _id, std::string _content, time_t time, int sender){
	id = _id;
	content = _content;
	sendTime = time;
	senderId = sender;
	type = text;
};

Message::Message(const Message& mes){
	id = mes.id;
	senderId = mes.senderId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = text;
};

Message Message::operator=(const Message& mes){
	return Message(mes);
}

//
//end of (Text)Message section
//


//
//VoiceMessage section
//
VoiceMessage::VoiceMessage(){ 
	id = -1;
	content = "";
	sendTime = 0;
	senderId = 0;
	type = voice;
};

VoiceMessage::VoiceMessage(int _id) { 
	id = _id;
	content = "";
	sendTime = 0;
	senderId = 0;
	type = voice;
};

VoiceMessage::VoiceMessage(std::string _content, time_t time, int sender){
	id = 0;
	content = _content;
	sendTime = time;
	senderId = sender;
	type = voice;
};

VoiceMessage::VoiceMessage(int _id, std::string _content, time_t time, int sender){
	id = _id;
	content = _content;
	sendTime = time;
	senderId = sender;
	type = voice;
};

VoiceMessage::VoiceMessage(const VoiceMessage& mes){
	id = mes.id;
	senderId = mes.senderId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = voice;
};

VoiceMessage VoiceMessage::operator=(const VoiceMessage& mes){
	return VoiceMessage(mes);
}

//
//end of VoiceMessage section
//