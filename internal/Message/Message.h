#ifndef MESSAGE
#define MESSAGE

#include "string"
#include "User.h"

class iMessage{
	protected:
		int id;
		User sender;
};

class Message: public iMessage{
	public:
		Message(std::string, User);
		std::string content;
};

#endif