#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include "Handler.h"
#include "Request.h"
#include "Response.h"

class GetMessageFromChat: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		const std::string REQUESTED_METHOD = "GET";
		const std::string REQUESTED_TARGET = "/chat/message/list";
};

class CreateChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		const std::string REQUESTED_METHOD = "POST";
		const std::string REQUESTED_TARGET = "/chat/create";
};

class JoinChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		const std::string REQUESTED_METHOD = "POST";
		const std::string REQUESTED_TARGET = "/chat/join";
};

class FindChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
	private:
		const std::string REQUESTED_METHOD = "GET";
		const std::string REQUESTED_TARGET = "/chat/find";
};
/*
// ???
class NotifyUsers: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};
*/
#endif