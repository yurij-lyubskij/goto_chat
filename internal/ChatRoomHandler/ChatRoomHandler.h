#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include <memory>
#include "DBRepo.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"

//Is used when user need to download new N messages from chat
class GetMessageFromChat: public iHandler{
	public:
		GetMessageFromChat(DBConnection<iConnection>* conn): connections(conn){};
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		DBConnection<iConnection>* connections;
		const std::string REQUESTED_TARGET = "/chat/message/list";
		std::vector<std::string> split(const std::string&);
};

//Is used when chat is created (first members are chosen beforehand)
class CreateChatRoom: public iHandler{
	public:
		CreateChatRoom(DBConnection<iConnection>* conn): connections(conn){};
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		DBConnection<iConnection>* connections;
		const std::string REQUESTED_TARGET = "/chat/create";
		std::vector<std::string> split(const std::string&);
};

//Is used when one user tries to join existing chat
class JoinChatRoom: public iHandler{
	public:
		JoinChatRoom(DBConnection<iConnection>* conn): connections(conn){};
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		DBConnection<iConnection>* connections;
		const std::string REQUESTED_TARGET = "/chat/join";
		std::vector<std::string> split(const std::string&);
};

//Is used when user search for chats by name
class FindChatRoom: public iHandler{
	public:
		FindChatRoom(DBConnection<iConnection>* conn): connections(conn){};
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		DBConnection<iConnection>* connections;
		const std::string REQUESTED_TARGET = "/chat/find";
		std::vector<std::string> split(const std::string&);
};

#endif