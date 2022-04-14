#ifndef SERVER_REDBREPO
#define SERVER_REDBREPO

#include "DBRepo.h"

class reUserRepo: public iUserRepo{
	MOCK_METHOD(bool, doesExist, (int), override);
	MOCK_METHOD(User*, getById, (int[], int), override);
	MOCK_METHOD(bool, update, (User[], len), override);
	MOCK_METHOD(bool, put, (User[], len), override);
	MOCK_METHOD(User*, getChatMembers, (ChatRoom), override);
	MOCK_METHOD(User*, getSender, (Message), override);
};

class ChatRepo: public iChatRepo{
	MOCK_METHOD(bool, doesExist, (int), override);
	MOCK_METHOD(ChatRoom*, getById, (int[], int), override);
	MOCK_METHOD(bool, update, (CharRoom[], len), override);
	MOCK_METHOD(bool, put, (ChatRoom[], len), override);
	MOCK_METHOD(bool, addUserToChat, (ChatRoom, User), override);
	MOCK_METHOD(ChatRoom, getMesChat, (Message), override);
	MOCK_METHOD(ChatRoom*, getUserChats, (User), override);
};

class MessageRepo: public iMessageRepo{
	MOCK_METHOD(bool, doesExist, (int), override);
	MOCK_METHOD(ChatRoom*, getById, (int[], int), override);
	MOCK_METHOD(bool, update, (CharRoom[], len), override);
	MOCK_METHOD(bool, put, (ChatRoom[], len), override);
	MOCK_METHOD(bool, addUserToChat, (ChatRoom, User), override);
	MOCK_METHOD(ChatRoom, getMesChat, (Message), override);
	MOCK_METHOD(ChatRoom*, getUserChats, (User), override);
		bool doesEsixt(int id);
		Message* getByID(int id[], int len);
		bool update(Message mes[], int len);
		bool put(Message mes[], int len);
		Message* getFromRange(int start, int end, Chat chat);
};

#endif