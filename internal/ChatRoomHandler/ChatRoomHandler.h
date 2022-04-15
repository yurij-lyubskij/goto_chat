#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include "Handler.h"
#include "Request.h"
#include "Response.h"

class GetMessageFromChat: public iHandler{
	public:
		bool canHandle(Request);
		Response handle(Request);
};

class CreateChatRoom: public iHandler{
	public:
		bool canHandle(Request);
		Response handle(Request);
};

class JoinChatRoom: public iHandler{
	public:
		bool canHandle(Request);
		Response handle(Request);
};

class FindChatRoom: public iHandler{
	public:
		bool canHandle(Request);
		Response handle(Request);
};

class NotifyUsers: public iHandler{
	public:
		bool canHandle(Request);
		Response handle(Request);
};

#endif