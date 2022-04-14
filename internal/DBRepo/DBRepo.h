#ifndef DATA_BASE_REPOS
#define DATA_BASE_REPOS

#include <string>
#include <time.h>

#include "ChatRoom.h"
#include "User.h"
#include "DBConnection.h"
#include "Message.h"

enum DBObjectType { user, chat, message, input };

typedef struct{
	int id;
	std::string phone;
	std::string name;
} UserDB;

typedef struct{
	int id;
	std::string name;
} ChatDB;

typedef struct{
	int id;
	int senderID;
	time_t time;
} MessageDB;

typedef struct{
	int id;
	FILE* content;
} InputDB;

//Interface Block
class iUserRepo{
	private:
		DBConnection *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual User* getByID(int id[], int len);
		virtual bool update(User users[], int len);
		virtual bool put(User usrs[], int len);
		virtual User* getChatMembers(ChatRoom chat);
		virtual User* getSender(Message mes);
};

class iChatRepo{
	private:
		DBConnection *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual ChatRoom* getByID(int id[], int len);
		virtual bool update(ChatRoom chats[], int len);
		virtual bool put(ChatRoom chats[], int len);
		virtual bool addUserToChat(ChatRoom chat, User user);
		virtual ChatRoom getMesChat(Message mes);
		virtual ChatRoom* getUserChats(User user);
};

class iMessageRepo{
	private:
		DBConnection *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual Message* getByID(int id[], int len);
		virtual bool update(Message mes[], int len);
		virtual bool put(Message mes[], int len);
		virtual Message* getFromRange(int start, int end, ChatRoom chat);
};

//Declaration block
class UserRepo: public iUserRepo{
	public:
		UserRepo(DBConnection*);
		bool doesEsixt(int id);
		User* getByID(int id[], int len);
		bool update(User users[], int len);
		bool put(User usrs[], int len);
		User* getChatMembers(ChatRoom chat);
		User* getSender(Message mes);
};

class ChatRepo: public iChatRepo{
	public:
		bool doesEsixt(int id);
		ChatRoom* getByID(int id[], int len);
		bool update(ChatRoom chats[], int len);
		bool put(ChatRoom chats[], int len);
		bool addUserToChat(ChatRoom chat, User user);
		ChatRoom getMesChat(Message mes);
		ChatRoom* getUserChats(User user);
};

class MessageRepo: public iMessageRepo{
	public:
		bool doesEsixt(int id);
		Message* getByID(int id[], int len);
		bool update(Message mes[], int len);
		bool put(Message mes[], int len);
		Message* getFromRange(int start, int end, ChatRoom chat);
};

/*
class InputRepo: public DBRepo{
	private:
		DBConnection *connection;
	public:
		bool doesEsixt(int id);
		Input* getByID(int id[], int len);
		bool update(Inputs inputs[], int len);
		bool put(Inputs inputs[], int len);
		Inputs* getInputs(Message mes);
};
*/

#endif