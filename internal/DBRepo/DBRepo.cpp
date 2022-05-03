#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "DBRepo.h"
#include "User.h"
#include "Message.h"

//
//DBObject Section
//

        DBObject::DBObject(){};
		DBObject::DBObject(const DBObject& obj): type(obj.type), attr(obj.attr){};
		DBObject::~DBObject(){};
        DBObject::DBObject(const UserDB& usr){};
        DBObject::DBObject(const ChatDB& chat){};
        DBObject::DBObject(const MessageDB& mes){};
		DBObject& DBObject::operator=(const DBObject& obj){
			type = obj.type;
			attr = obj.attr;
			return *this;
		};

//
//end of DBObject Section
//

//
//UserRepo Section
//
/*
bool UserRepo::doesExist(int id){
	return false;
};

std::vector<User> UserRepo::getByID(std::vector<int> id){
	std::vector<User> usrs;
	return usrs;
};

bool UserRepo::update(std::vector<User> users){
	return false;
};

bool UserRepo::put(std::vector<User> users){
	if ( users.empty() ) return false;

	std::shared_ptr<iConnection> conn = connection->connection();

	int len = users.size();
	std::vector<DBObject> objects(len);
	UserDB tempUser;

	for(int i = 0; i < len; ++i) {
		tempUser = { (int) users[i].Id, users[i].Name, users[i].PhoneNumber };
		objects[i] = DBObject(tempUser);
	};
	return conn->exec(putIt, objects);
};

std::vector<User> UserRepo::getChatMembers(ChatRoom chat){
	std::vector<User> usrs;
	return usrs;
};

std::vector<User> UserRepo::getSender(Message mes){
	std::vector<User> usrs;
	return usrs;
};
*/
//
//end of UserRepo Section
//

//
//ChatRepo Section
//

bool ChatRepo::doesExist(int id){
	return false;
};

std::vector<ChatRoom> ChatRepo::getByID(std::vector<int> id){
	std::vector<ChatRoom> chats;
	return chats;
};

bool ChatRepo::update(std::vector<ChatRoom> chats){
	return false;
};

bool ChatRepo::put(std::vector<ChatRoom> chats){
	if ( chats.empty() ) return false;

	std::shared_ptr<iConnection> conn = connection->connection();

	int len = chats.size();
	std::vector<DBObject> objects(len);
	ChatDB tempChat;

	for(int i = 0; i < len; ++i) {
		tempChat = { chats[i].getId(), chats[i].getName() };
		objects[i] = DBObject(tempChat);
	};
	return conn->exec(putIt, objects);
};

bool ChatRepo::addUserToChat(const ChatRoom &chat, const User &user){
	return false;
};

ChatRoom ChatRepo::getMesChat(Message mes){
	return ChatRoom();
};

std::vector<ChatRoom> ChatRepo::getUserChats(User user){
	std::vector<ChatRoom> chats;
	return chats;
};
//
//end of ChatRepo Section
//

//
//MessageRepo Section
//
bool MessageRepo::doesExist(int id){
	return false;
};
std::vector<iMessage> MessageRepo::getByID(std::vector<int> id){
	std::vector<iMessage> messages;
	return messages;
};

bool MessageRepo::update(std::vector<iMessage> mes){
	return false;
};

bool MessageRepo::put(std::vector<iMessage> mes){
	if ( mes.empty() ) return false;

	std::shared_ptr<iConnection> conn = connection->connection();

	int len = mes.size();
	std::vector<DBObject> objects(len);
	MessageDB tempMes;

	for(int i = 0; i < len; ++i) {
		tempMes = { mes[i].getId(), (int) mes[i].getSender().Id, mes[i].getTime(), mes[i].getContent() };
		objects[i] = DBObject(tempMes);
	};
	return conn->exec(putIt, objects);
};

std::vector<iMessage> MessageRepo::getFromRange(int start, int end,const ChatRoom &chat){
	std::vector<iMessage> messages;
	return messages;
};

//
//end of MessageRepo Section
//