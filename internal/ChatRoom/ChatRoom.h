#ifndef CHATROOM
#define CHATROOM

#include <vector>

#include "User.h"
#include "Message.h"

class iChatRoom{
	protected:
		int id;
		std::string name;
	public:
		int getId() const { return id; };
		std::string getName() const { return name; };
};

class ChatRoom: public iChatRoom{
	public:
		ChatRoom();					//Creates empty(false) object
		ChatRoom(int);
		ChatRoom(const std::string&);		//Creates object with id = 0 to add to database
		ChatRoom(int, const std::string&);
		ChatRoom(const ChatRoom&);
		ChatRoom& operator=(const ChatRoom&);
};

#endif