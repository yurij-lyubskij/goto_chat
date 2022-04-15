#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

#include "Handler.h"
#include "Request.h"
#include "Response.h"

class GetMessageFromChat: public iHandler{
	public:
		bool CanHandle(Request) override;
		Response Handle(Request);
};


class JoinChatRoom: public iHandler{
	public:
		bool CanHandle(Request);
		Response Handle(Request);
};


class NotifyUsers: public iHandler{
	public:
		bool CanHandle(Request);
		Response Handle(Request);
};

#endif