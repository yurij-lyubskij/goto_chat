#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <time.h>

#include "User.h"

enum MessegeType{ textMessage, voiceMessage };

class iMessage{
	protected:
		int id;
		std::string content;
		time_t sendTime;
		int senderId;
		enum MessegeType type;
	public:
		iMessage(): id(0), content(""),
			sendTime(0), senderId(0), type(textMessage){};
		iMessage(int _id, std::string _content, time_t _sendTime , int _senderId , enum MessegeType _type): id(_id), content(_content),
			sendTime(_sendTime), senderId(_senderId), type(_type){};
		int getId() const { return id; };
		int getSender() const { return senderId; };
		time_t getTime() const { return sendTime; };
		std::string getContent() const { return content; };
		enum MessegeType getType() const { return type; };
};

class Message: public iMessage{
	protected:
	public:
		Message();													//Creates empty(false) object
		Message(int);
		Message(std::string, time_t, int);							//Creates object with id = 0 to add to database
		Message(int, std::string, time_t, int);
		Message(const Message&);
		Message(const iMessage&);
		Message operator=(const Message&);

};

class VoiceMessage: public iMessage{
	protected:
	public:
		VoiceMessage();													//Creates empty(false) object
		VoiceMessage(int);
		VoiceMessage(std::string, time_t, int);							//Creates object with id = 0 to add to database
		VoiceMessage(int, std::string, time_t, int);
		VoiceMessage(const VoiceMessage&);
		VoiceMessage(const iMessage&);
		VoiceMessage operator=(const VoiceMessage&);
};

#endif