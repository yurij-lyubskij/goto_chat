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
        DBObject::DBObject(const User& usr){};
        DBObject::DBObject(const ChatRoom& chat){};
        DBObject::DBObject(const iMessage& mes){};
User DBObject::toUser(){
	User usr;
	if( type != user ) return usr;

	usr.Id = std::stoi(attr[0]);
	usr.Name = attr[1];
	usr.PhoneNumber = attr[2];
	return usr;
};
ChatRoom DBObject::toChat(){
	if( type != chat ) return ChatRoom();

	return ChatRoom(std::stoi(attr[0]), attr[1]);
};
Message DBObject::toMessage(){
	if( type != message ) return Message();

	return Message(std::stoi(attr[0]), attr[1], std::stoi(attr[2]), User(std::stoi(attr[3])));
};
DBObject DBObject::operator=(const DBObject& obj){
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
	ChatRoom tempChat;

	for(int i = 0; i < len; ++i) objects[i] = DBObject(chats[i]);
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

	for(int i = 0; i < len; ++i) {
		objects[i] = DBObject(mes[i]);
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