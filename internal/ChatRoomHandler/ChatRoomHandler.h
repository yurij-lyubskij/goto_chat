#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include "Handler.h"
#include "Request.h"
#include "Response.h"

class GetMessageFromChat: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};

class CreateChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};

class JoinChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};

class FindChatRoom: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};

class NotifyUsers: public iHandler{
	public:
		bool canHandle(Request) override;
		Response handle(Request) override;
};

#endif