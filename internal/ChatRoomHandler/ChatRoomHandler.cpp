#include "ChatRoomHandler.h"
#include "ChatRoom.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"
//GetMessageFromChat
bool GetMessageFromChat::CanHandle(Request request){
	return false;
};

Response GetMessageFromChat::Handle(Request request){
	return Response();
};
//end of GetMessageFromChat


//JoinChatRoom
bool JoinChatRoom::CanHandle(Request request){
	return false;
};

Response JoinChatRoom::Handle(Request request){
	return Response();
};
//end of JoinChatRoom

//end of FindChatRoom

//NotifyUsers
bool NotifyUsers::CanHandle(Request request){
	return false;
};

Response NotifyUsers::Handle(Request request){
	return Response();};
//end of NotifyUsers