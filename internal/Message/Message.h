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
		std::string content;
};

#endif