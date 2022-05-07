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
		Message(){ id = 0; };
		Message(std::string, time_t, User){};
		Message(int, std::string, time_t, User){};
		Message(const Message&);
		Message operator=(const Message&);

};

class VoiceMessage: public iMessage{

};

#endif