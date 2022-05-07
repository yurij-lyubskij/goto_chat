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
		virtual bool addUser(User user) = 0;
		virtual bool removeUser(User user) = 0;
		virtual bool reactOn(Message mes) = 0;
		virtual std::vector<User> getMembers() = 0;
};

class ChatRoom: public iChatRoom{
	public:
		ChatRoom();					//Creates empty(false) object
		ChatRoom(int);				//Takes out chat from data base by id
		ChatRoom(int, std::string);	//Doesn't refer to data base, just create new object
		ChatRoom(const ChatRoom&);
		bool addUser(User user) override;
		bool removeUser(User user) override;
		bool reactOn(Message mes) override;
		std::vector<User> getMembers() override;
		ChatRoom operator=(const ChatRoom&);
};

#endif