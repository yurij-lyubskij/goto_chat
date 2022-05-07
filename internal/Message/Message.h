#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <time.h>

#include "User.h"

class iMessage{
	protected:
		int id;
		time_t sendTime;
		std::string content;
		User sender;
	public:
		int getId() const { return id; };
		User getSender() const { return sender; };
		time_t getTime() const { return sendTime; };
		std::string getContent() const { return content; };
};

class Message: public iMessage{
	public:
		Message(){ id = 0; };					//Creates empty(false) object
		Message(std::string, time_t, User){};	//Creates object that is not in database
		Message(int, std::string, time_t, User){};
		Message(const Message&);
		Message operator=(const Message&);

};

class VoiceMessage: public iMessage{

};

#endif