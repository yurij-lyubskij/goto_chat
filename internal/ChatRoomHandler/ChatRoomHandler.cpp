#include "ChatRoomHandler.h"
#include "ChatRoom.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"
//GetMessageFromChat
bool GetMessageFromChat::canHandle(Request request){
	return false;
};

Response GetMessageFromChat::handle(Request request){
	return Response();
};
//end of GetMessageFromChat

//CreateChatRoom
bool CreateChatRoom::canHandle(Request request){
	return false;
};

Response CreateChatRoom::handle(Request request){
	return Response();
};
//end of CreateChatRoom

//JoinChatRoom
bool JoinChatRoom::canHandle(Request request){
	return false;
};

Response JoinChatRoom::handle(Request request){
	return Response();
};
//end of JoinChatRoom

//FindChatRoom
bool FindChatRoom::canHandle(Request request){
	return false;
};

Response FindChatRoom::handle(Request request){
	return Response();
};
//end of FindChatRoom

//NotifyUsers
bool NotifyUsers::canHandle(Request request){
	return false;
};

Response NotifyUsers::handle(Request request){
	return Response();
};
//end of NotifyUsers