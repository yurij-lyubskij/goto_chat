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
		int senderId;
	public:
		int getId() const { return id; };
		int getSender() const { return senderId; };
		time_t getTime() const { return sendTime; };
		std::string getContent() const { return content; };
};

class Message: public iMessage{
	public:
		Message();													//Creates empty(false) object
		Message(int);
		Message(std::string, time_t, int);							//Creates object with id = 0 to add to database
		Message(int, std::string, time_t, int);
		Message(const Message&);
		Message operator=(const Message&);

};

class VoiceMessage: public iMessage{

};

#endif