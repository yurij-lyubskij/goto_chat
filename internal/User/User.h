#ifndef GOTO_CHAT_USER_H
#define GOTO_CHAT_USER_H

#include <string>

class User {
	public:
		std::string Name;
    	size_t Id;
    	std::string PhoneNumber;
		User();
		User(int);
};

#endif