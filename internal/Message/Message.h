#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <time.h>

#include "User.h"

class iMessage{
	protected:
		int id;
		User sender;
		time_t sendTime;
		std::string content;
	public:
		int getId(){ return id; };
		User getSender(){ return sender; };
		time_t getTime(){ return sendTime; };
		std::string getContent(){ return content; };
};

class Message: public iMessage{
	public:
		Message(std::string, time_t, User){};
		Message(int, std::string, time_t, User){};

};

class VoiceMessage: public iMessage{

};

#endif