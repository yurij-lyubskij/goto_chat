#ifndef SERVER_REDBREPO
#define SERVER_REDBREPO

#include <vector>
#include <gmock/gmock.h>
#include "DBRepo.h"

class reUserRepo: public iUserRepo{
	public:
		MOCK_METHOD(bool, doesExist, (int), () );
		MOCK_METHOD(std::vector<User>, getById, (std::vector<int>), ());
		MOCK_METHOD(bool, update, (std::vector<User>), ());
		MOCK_METHOD(bool, put, (std::vector<User>), ());
		MOCK_METHOD(std::vector<User>, getChatMembers, (ChatRoom), ());
		MOCK_METHOD(std::vector<User>, getSender, (Message), ());
};

class reChatRepo: public iChatRepo{
	public:
		MOCK_METHOD(bool, doesExist, (int), ());
		MOCK_METHOD(std::vector<ChatRoom>, getById, (std::vector<int>), ());
		MOCK_METHOD(bool, update, (std::vector<ChatRoom>), ());
		MOCK_METHOD(bool, put, (std::vector<ChatRoom>), ());
		MOCK_METHOD(bool, addUserToChat, (ChatRoom, User), ());
		MOCK_METHOD(ChatRoom, getMesChat, (Message), ());
		MOCK_METHOD(std::vector<ChatRoom>, getUserChats, (User), ());
};

class reMessageRepo: public iMessageRepo{
	public:
		MOCK_METHOD(bool, doesExist, (int), ());
		MOCK_METHOD(std::vector<Message>, getById, (int[], int), ());
		MOCK_METHOD(bool, update, (std::vector<Message>), ());
		MOCK_METHOD(bool, put, (std::vector<Message>),());
		MOCK_METHOD(std::vector<Message>, getFromRange, (int, int, ChatRoom), ());
};

#endif