#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include <algorithm>

#include "DBRepo.h"
#include "User.h"
#include "Message.h"

//
//DBObject Section
//

DBObject::DBObject(){};

DBObject::DBObject(const DBObject& obj): type(obj.type), attr(obj.attr){};

DBObject::~DBObject(){};
//
//object to DBObject section
//
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
//
//enod of object to DBObject section
//

//
//DBObject to object section
//
DBObject::operator User(){
	User usr;
	if( type != user ) return usr;

	usr.Id = std::stoi(attr[0]);
	usr.Name = attr[1];
	usr.PhoneNumber = attr[2];
	return usr;
};

DBObject::operator ChatRoom(){
	if( type != chat ) return ChatRoom(-1);
	return ChatRoom(std::stoi(attr[0]), attr[1]);
};

DBObject::operator iMessage(){
	if( type != message ) return Message(-1);

	return Message(std::stoi(attr[0]), attr[1], std::stoi(attr[2]), std::stoi(attr[3]));
};

//
//end of DBObject to object section
//

DBObject DBObject::operator=(const DBObject& obj){
	type = obj.type;
	attr = obj.attr;
	return *this;
};


std::vector<std::string> iConnection::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ' ')) {
            elems.push_back(item);
    }
    return elems;
}
//
//end of DBObject Section
//

/*
//
//UserRepo Section
//
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

//
//end of UserRepo Section
//
*/

//
//ChatRepo Section
//

ChatRepo::ChatRepo(){};

ChatRepo::ChatRepo(DBConnection<iConnection> *conn){
	connection = conn;
};

bool ChatRepo::doesExist(int id){
	if ( id < 1 ) return false;

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB
	ChatRoom cht(id);														//empty object just to check
	DBObject obj(cht);
	std::vector<DBObject> objects(1);
	objects[0] = obj;
	DBRequest request = { checkIt, chat, "" };
	bool res = conn->exec(request, objects);								//exec with "chekIt" doesn't need proper object and will use only id
	connection->freeConnection(conn);										//return connection to the queue
	return res;
};

std::vector<ChatRoom> ChatRepo::getByID(std::vector<int> ids){
	std::vector<ChatRoom> chats(1);
	if ( ids.empty() ) return chats;
	if(std::find(ids.begin(), ids.end(), -1) != ids.end()) return chats;
	
	int len = ids.size();
	
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB
	DBRequest request;
	request.operation = getFew;
	request.objectType = chat;
	request.request = "id";
	for( int i = 0; i < len; ++i) request.request += " " + std::to_string(ids[i]);
	std::vector<DBObject> result = conn->get(request);

	len = result.size();													//objects with some ids might don't exist so check size
	chats = std::vector<ChatRoom>();
	for( int i = 0; i < len; ++i) chats.push_back(result[i]);
	connection->freeConnection(conn);										//return connection to the queue

	return chats;
};

bool ChatRepo::update(std::vector<ChatRoom> chats){
	if ( chats.empty() ) return true;
	
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = chats.size();
	std::vector<DBObject> objects(len);
	ChatRoom tempChat;

	for(int i = 0; i < len; ++i) {
		objects[i] = DBObject(chats[i]);
		if ( chats[i].getId() < 1 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	}

	DBRequest request = { updateIt, chat, "" };

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;
};

bool ChatRepo::put(std::vector<ChatRoom> chats){
	if ( chats.empty() ) return true;

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = chats.size();
	std::vector<DBObject> objects(len);
	ChatRoom tempChat;
	
	for(int i = 0; i < len; ++i) {
		objects[i] = DBObject(chats[i]);
		if ( chats[i].getId() != 0 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	}

	DBRequest request = { putIt, chat, "" };

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;
};

bool ChatRepo::addUsersToChat(const ChatRoom &updatedChat, std::vector<User> users){

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = users.size()+1;
	std::vector<DBObject> objects(len);
	objects[0] = DBObject(updatedChat);

	for(int i = 1; i < len; ++i) {
		objects[i] = DBObject(users[i]);
		if ( users[i].Id < 1 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	}

	DBRequest request = { addMembers, chat, "" };

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;
};


bool ChatRepo::removeUsersFromChat(const ChatRoom &updatedChat, std::vector<User> users){

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = users.size()+1;
	std::vector<DBObject> objects(len);
	objects[0] = DBObject(updatedChat);

	for(int i = 1; i < len; ++i) {
		objects[i] = DBObject(users[i]);
		if ( users[i].Id < 1 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	}


	DBRequest request = { removeMembers, chat, "remove" };
	return conn->exec( request , objects);
};

ChatRoom ChatRepo::getMesChat(Message mes){
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	DBRequest request;
	request.operation = getMessageOrigin;
	request.objectType = chat;
	request.request = std::to_string(mes.getId());
	
	std::vector<DBObject> objects = conn->get(request);

	connection->freeConnection(conn);										//return connection to the queue

	return (ChatRoom) objects[0];
};

std::vector<ChatRoom> ChatRepo::getUserChats(const User& user){

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	DBRequest request;
	request.operation = getChatsofUser;
	request.objectType = chat;
	request.request = std::to_string(user.Id);
	
	std::vector<DBObject> objects = conn->get(request);
	int len = objects.size();

	std::vector<ChatRoom> chats(len);
	for(int i = 0; i < len; ++i) chats[i] = ChatRoom(objects[i]);

	connection->freeConnection(conn);										//return connection to the queue

	return chats;
};
//
//end of ChatRepo Section
//

//
//MessageRepo Section
//

MessageRepo::MessageRepo(){};

MessageRepo::MessageRepo(DBConnection<iConnection>* conn){
	connection = conn;
};

bool MessageRepo::doesExist(int id){
	if ( id < 1 ) return true;
	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	Message mes(id);														//empty object just to check
	DBObject obj(mes);
	std::vector<DBObject> objects(1);

	objects[0] = obj;
	DBRequest request = { checkIt, message, "" };							//exec with "chekIt" doesn't need proper object and will use only id

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;
};

std::vector<iMessage> MessageRepo::getByID(std::vector<int> ids){
	std::vector<iMessage> mesages(1);
	if ( ids.empty() ) return mesages;
	if ( std::find(ids.begin(), ids.end(), -1) != ids.end() ||
		std::find(ids.begin(), ids.end(), -1) != ids.end() ) return mesages;
	int len = ids.size();

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	DBRequest request;
	request.operation = getFew;
	request.objectType = message;
	request.request = "id";
	for( int i = 0; i < len; ++i) request.request += " " + std::to_string(ids[i]);
	std::vector<DBObject> result = conn->get(request);

	len = result.size();													//objects with some ids might don't exist so check size
	mesages = std::vector<iMessage>(len);
	for( int i = 0; i < len; ++i) mesages[i] = (iMessage) result[i];

	connection->freeConnection(conn);										//return connection to the queue

	return mesages;
};

bool MessageRepo::update(std::vector<iMessage> mes){
	if ( mes.empty() ) return true;

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = mes.size();
	std::vector<DBObject> objects(len);

	for(int i = 0; i < len; ++i) {
		objects[i] = DBObject(mes[i]);
		if ( mes[i].getId() < 1 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	};

	DBRequest request = { updateIt, message, "" };

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;return conn->exec( request , objects);
};

bool MessageRepo::put(std::vector<iMessage> mes){
	if ( mes.empty() ) return true;

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	int len = mes.size();
	std::vector<DBObject> objects(len);

	for(int i = 0; i < len; ++i) {
		objects[i] = DBObject(mes[i]);
		if ( mes[i].getId() != 0 ) {
			connection->freeConnection(conn);										//return connection to the queue
			return false;
		}
	};
	
	DBRequest request = { putIt, message, "" };

	bool res = conn->exec( request , objects);
	connection->freeConnection(conn);										//return connection to the queue

	return res;
};

std::vector<iMessage> MessageRepo::getFromRange(int start, int end,const ChatRoom &chat){

	std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

	DBRequest request;
	request.operation = getRange;
	request.objectType = message;
	request.request = std::to_string(start) + " " + std::to_string(end);

	std::vector<DBObject> result = conn->get(request);

	int len = result.size();													//objects with some ids might don't exist so check size
	std::vector<iMessage> mesages = std::vector<iMessage>(len);

	for( int i = 0; i < len; ++i ) mesages[i] = (iMessage) result[i];

	connection->freeConnection(conn);										//return connection to the queue

	return mesages;
};

//
//end of MessageRepo Section
//