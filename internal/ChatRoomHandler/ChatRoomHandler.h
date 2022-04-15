#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include "Handler.h"
#include "Request.h"
#include "Response.h"

class GetMessageFromChat: public iHandler{
	bool canHandle(Request);
	Response handle(Request);
};

class CreateChatRoom: public iHandler{
	bool canHandle(Request);
	Response handle(Request);
};

class JoinChatRoom: public iHandler{
	bool canHandle(Request);
	Response handle(Request);
};

class FindChatRoom: public iHandler{
	bool canHandle(Request);
	Response handle(Request);
};

class NotifyUsers: public iHandler{
	bool canHandle(Request);
	Response handle(Request);
};

#endif