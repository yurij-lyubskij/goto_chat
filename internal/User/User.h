#ifndef GOTO_CHAT_USER_H
#define GOTO_CHAT_USER_H

#include <string>

class User {
	public:
		std::string Name;
		size_t Id;
		std::string PhoneNumber;
		std::string password;
		User();
		User(int);
};

#endif