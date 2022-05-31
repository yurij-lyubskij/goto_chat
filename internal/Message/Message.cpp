#include "Message.h"
#include <stdexcept>

//
//(Text)Message section
//

Message::Message(){ 
	id = -1;
	content = "";
	sendTime = 0;
	senderId = 0;
	chatId = 0;
	type = textMessage;
};

Message::Message(int _id) { 
	id = _id;
	content = "";
	sendTime = 0;
	senderId = 0;
	chatId = 0;
	type = textMessage;
};

Message::Message(const std::string& _content, time_t time, int sender, int chat){
	id = 0;
	content = _content;
	sendTime = time;
	senderId = sender;
	chatId = chat;
	type = textMessage;
};

Message::Message(int _id, const std::string& _content, time_t time, int sender, int chat){
	id = _id;
	content = _content;
	sendTime = time;
	senderId = sender;
	chatId = chat;
	type = textMessage;
};

Message::Message(const Message& mes){
	id = mes.id;
	senderId = mes.senderId;
	chatId = mes.chatId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = textMessage;
};

Message::Message(const iMessage& mes){
	if( mes.getType() != textMessage ) {
		throw std::invalid_argument("the iMessage isn't text message");
	}
	id = mes.getId();
	senderId = mes.getSender();
	chatId = mes.getChat();
	sendTime = mes.getTime();
	content = mes.getContent();
	type = textMessage;
};

Message& Message::operator=(const Message& mes){
	id = mes.id;
	senderId = mes.senderId;
	chatId = mes.chatId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = textMessage;
	return *this;
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
	chatId = 0;
	type = voiceMessage;
};

VoiceMessage::VoiceMessage(int _id) { 
	id = _id;
	content = "";
	sendTime = 0;
	senderId = 0;
	chatId = 0;
	type = voiceMessage;
};

VoiceMessage::VoiceMessage(const std::string& _content, time_t time, int sender, int chat){
	id = 0;
	content = _content;
	sendTime = time;
	senderId = sender;
	chatId = chat;
	type = voiceMessage;
};

VoiceMessage::VoiceMessage(int _id, const std::string& _content, time_t time, int sender, int chat){
	id = _id;
	content = _content;
	sendTime = time;
	senderId = sender;
	chatId = chat;
	type = voiceMessage;
};

VoiceMessage::VoiceMessage(const VoiceMessage& mes){
	id = mes.id;
	senderId = mes.senderId;
	chatId = mes.chatId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = voiceMessage;
};

VoiceMessage::VoiceMessage(const iMessage& mes){
	if( mes.getType() != voiceMessage ) {
		throw std::invalid_argument("the iMessage isn't voice message");
	}
	id = mes.getId();
	senderId = mes.getSender();
	chatId = mes.getChat();
	sendTime = mes.getTime();
	content = mes.getContent();
	type = voiceMessage;
};

VoiceMessage& VoiceMessage::operator=(const VoiceMessage& mes){
	id = mes.id;
	senderId = mes.senderId;
	chatId = mes.chatId;
	sendTime = mes.sendTime;
	content = mes.content;
	type = voiceMessage;
	return *this;
}

//
//end of VoiceMessage section
//