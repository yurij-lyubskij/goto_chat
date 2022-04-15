#ifndef CHATROOM
#define CHATROOM

#include <vector>

#include "User.h"
#include "Message.h"

class iChatRoom{
	protected:
		int id;
	public:
		virtual bool addUser(User user) = 0;
		virtual bool removeUser(User user) = 0;
		virtual bool reactOn(Message mes) = 0;
		virtual std::vector<User> getMembers();
};

class ChatRoom: public iChatRoom{
	public:
		bool addUser(User user);
		bool removeUser(User user);
		bool reactOn(Message mes);
		std::vector<User> getMembers();
};

#endif