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

DBObject::DBObject(const User& usr){
	type = user;
	attr = std::vector<std::string>(3);

	std::string tempAttr;
	tempAttr = std::to_string(usr.Id);
	attr[0] = tempAttr;
	tempAttr = usr.Name;
	attr[1] = tempAttr;
	tempAttr = usr.PhoneNumber;
	attr[2] = tempAttr;
};

DBObject::DBObject(const ChatRoom& cht){
	type = chat;
	attr = std::vector<std::string>(2);

	std::string tempAttr;
	tempAttr = std::to_string(cht.getId());
	attr[0] = tempAttr;
	tempAttr = cht.getName();
	attr[1] = tempAttr;
};

DBObject::DBObject(const iMessage& mes){
	type = message;
	attr = std::vector<std::string>(4);

	std::string tempAttr;
	//id
	tempAttr = std::to_string(mes.getId());
	attr[0] = tempAttr;
	//content
	tempAttr = mes.getContent();
	attr[1] = tempAttr;
	//sendTime
	tempAttr = std::to_string(mes.getTime());
	attr[2] = tempAttr;
	//sender
	tempAttr = std::to_string(mes.getSender());
	attr[3] = tempAttr;
};

DBObject::operator User(){
	User usr;
	if( type != user ) return usr;

	usr.Id = std::stoi(attr[0]);
	usr.Name = attr[1];
	usr.PhoneNumber = attr[2];
	return usr;
};

DBObject::operator ChatRoom(){
	if( type != chat ) return ChatRoom();

	return ChatRoom(std::stoi(attr[0]), attr[1]);
};

DBObject::operator iMessage(){
	if( type != message ) return Message();

	return Message(std::stoi(attr[0]), attr[1], std::stoi(attr[2]), std::stoi(attr[3]));
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
	if ( id == 0 ) return false;
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	ChatRoom cht(id, "");													//empty object just to check
	DBObject obj(cht);
	std::vector<DBObject> objects(1);

	objects[1] = obj;
	return conn->exec(checkIt, objects);									//exec with "chekIt" doesn't need proper object and will use only id
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

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = chats.size();
	std::vector<DBObject> objects(len);
	ChatRoom tempChat;

	for(int i = 0; i < len; ++i) objects[i] = DBObject(chats[i]);
	return conn->exec(putIt, objects);
};

bool ChatRepo::addUsersToChat(const ChatRoom &chat, std::vector<User> users){
	return false;
};

bool ChatRepo::removeUsersFromChat(const ChatRoom &chat, std::vector<User> users){
	return false;
};

ChatRoom ChatRepo::getMesChat(Message mes){
	return ChatRoom();
};

std::vector<ChatRoom> ChatRepo::getUserChats(const User& user){
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
	if ( id == 0 ) return false;
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	Message mes(id, "", 0, 0);												//empty object just to check
	DBObject obj(mes);
	std::vector<DBObject> objects(1);

	objects[1] = obj;
	return conn->exec(checkIt, objects);									//exec with "chekIt" doesn't need proper object and will use only id
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

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

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