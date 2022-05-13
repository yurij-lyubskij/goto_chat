#include <sstream>
#include <vector>

#include "ChatRoomHandler.h"
#include "ChatRoom.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"
#include "DBRepo.h"
//GetMessageFromChat
bool GetMessageFromChat::canHandle(Request request){
	return request.target == REQUESTED_TARGET;
};

Response GetMessageFromChat::handle(Request request){
	Response response;
	response.cookie = request.cookie;
	response.method = request.method;
	response.body = "";
	std::vector<std::string> bodySplit = split(request.body);
	ChatRepo repo(connections);
	std::vector<int> res = repo.put({ChatRoom(bodySplit[0])});
	if( res.empty() ){ 
		response.statusCode = 400;
		return response;
	};

	ChatRoom chat(res[0], bodySplit[0]);
	int usrCount = std::stoi(bodySplit[1]);
	std::vector<User> usrs;
	
	for( int i = 0; i < usrCount; ++i) usrs.push_back(User(std::stoi(bodySplit[i+2])));
	repo.addUsersToChat(chat, usrs);
	response.statusCode = 200;
	return response;
};

std::vector<std::string> GetMessageFromChat::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ' ')) {
            elems.push_back(item);
    }
    return elems;
}
//end of GetMessageFromChat

//CreateChatRoom
bool CreateChatRoom::canHandle(Request request){
	return request.target == REQUESTED_TARGET;
};

Response CreateChatRoom::handle(Request request){
	Response response;
	response.cookie = request.cookie;
	response.method = request.method;
	response.body = "";

	std::vector<std::string> bodySplit = split(request.body);
	ChatRepo repo(connections);
	std::vector<ChatRoom> chts;
	chts.push_back(ChatRoom(bodySplit[0]));

	std::vector<int> res = repo.put(chts);
	if( res.empty() ){ 
		response.statusCode = 400;
		return response;
	};
	ChatRoom chat(res[0], bodySplit[0]);
	int usrCount = std::stoi(bodySplit[1]);
	std::vector<User> usrs;
	
	for( int i = 0; i < usrCount; ++i) usrs.push_back(User(std::stoi(bodySplit[i+2])));

	if ( repo.addUsersToChat(chat, usrs) ) response.statusCode = 200;
	else response.statusCode = 400;

	return response;
};

std::vector<std::string> CreateChatRoom::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ' ')) {
            elems.push_back(item);
    }
    return elems;
}
//end of CreateChatRoom

//JoinChatRoom
bool JoinChatRoom::canHandle(Request request){
	return request.target == REQUESTED_TARGET;
};

Response JoinChatRoom::handle(Request request){
	return Response();
};
//end of JoinChatRoom

//FindChatRoom
bool FindChatRoom::canHandle(Request request){
	return request.target == REQUESTED_TARGET;
};

Response FindChatRoom::handle(Request request){
	return Response();
};
//end of FindChatRoom
/*
//NotifyUsers
bool NotifyUsers::canHandle(Request request){
	return false;
};

Response NotifyUsers::handle(Request request){
	return Response();
};
//end of NotifyUsers
*/