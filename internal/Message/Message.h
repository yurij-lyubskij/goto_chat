#ifndef MESSAGE
#define MESSAGE

#include "string"
#include "User.h"

class iMessage{
	public:
		int id;
		User sender;
		std::string content;
};

class Message: public iMessage{
	public:
		Message(std::string, User){};
		Message(int, std::string, User){};

};

class VoiceMessage: public iMessage{

};

#endif