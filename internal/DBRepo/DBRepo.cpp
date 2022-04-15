#include <string>
#include <time.h>

#include "DBRepo.h"
#include "User.h"
#include "Message.h"

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
	return false;
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
	return false;
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
	return false;
};

std::vector<iMessage> MessageRepo::getFromRange(int start, int end,const ChatRoom &chat){
	std::vector<iMessage> messages;
	return messages;
};

//
//end of MessageRepo Section
//