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
		//virtual bool addUsers(std::vector<User> users, ChatRepo*) = 0;			//moved to chatRepo
		//virtual bool removeUsers(std::vector<User> users, ChatRepo*) = 0;
		virtual bool reactOn(Message mes) = 0;
		virtual std::vector<User> getMembers() = 0;
};

class ChatRoom: public iChatRoom{
	public:
		ChatRoom();					//Creates empty(false) object
		ChatRoom(int);				//Takes out chat from data base by id
		ChatRoom(int, std::string);	//Doesn't refer to data base, just create new object
		ChatRoom(const ChatRoom&);
		//bool addUsers(std::vector<User> users, ChatRepo*) override;
		//bool removeUsers(std::vector<User> users, ChatRepo*) override;
		bool reactOn(Message mes) override;
		std::vector<User> getMembers() override;
		ChatRoom operator=(const ChatRoom&);
};

#endif