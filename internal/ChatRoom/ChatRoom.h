#ifndef CHATROOM
#define CHATROOM

#include "User.h"

class iChatRoom{
	protected:
		int id;
		User members[];
	public:
		virtual bool addUser(User user) = 0;
		virtual bool removeUser(User user) = 0;
		virtual bool reactOn(Message mes) = 0;
		virtual User* getMembers();
};

class ChatRoom: public iChatRoom{
	public:
		bool addUser(User user);
		bool removeUser(User user);
		bool reactOn(Message mes);
		User* getMembers();
};

#endif