#ifndef CHATROOM_HANDLERS
#define CHATROOM_HANDLERS

//include IHandler
//include Request
//include Response

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

#endif