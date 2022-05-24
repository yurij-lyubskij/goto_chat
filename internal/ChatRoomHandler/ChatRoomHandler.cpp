#include <sstream>
#include <vector>


#include "ChatRoomHandler.h"
#include "ChatRoom.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"
#include "DBRepo.h"

//GetMessageFromChat
bool GetMessageFromChat::CanHandle(Request request){
    return request.target == REQUESTED_TARGET;
};

Response GetMessageFromChat::Handle(Request request){
    Response response;
    response.statusCode = OK;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.cookie = request.cookie;
    response.body = "";
    std::vector<std::string> bodySplit = split(request.body);
    MessageRepo repo(connections);

    if( bodySplit.size() != 4 ){
        response.statusCode = BadRequest;
        return response;
    };
    int start = std::stoi(bodySplit[2]);
    int end = std::stoi(bodySplit[2]) + std::stoi(bodySplit[3]) - 1;

    std::vector<iMessage> messages = repo.getFromRange(start, end, ChatRoom(std::stoi(bodySplit[0])));

    for( int i = 0; i < messages.size(); ++i ) {
        response.body += messages[i].getContent() + " " + std::to_string(messages[i].getTime()) + " " + std::to_string(messages[i].getSender()) + " " + std::to_string(messages[i].getChat()) + "\n";
    }

    response.statusCode = OK;
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
bool CreateChatRoom::CanHandle(Request request){
    return request.target == REQUESTED_TARGET;
};

Response CreateChatRoom::Handle(Request request){
    Response response;
    response.statusCode = OK;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.cookie = request.cookie;
    response.body = "";

    std::vector<std::string> bodySplit = split(request.body);
    ChatRepo repo(connections);
    std::vector<ChatRoom> chts;
    chts.push_back(ChatRoom(bodySplit[0]));

    std::vector<int> res = repo.put(chts);
    if( res.empty() ){
        response.statusCode = BadRequest;
        return response;
    };
    ChatRoom chat(res[0], bodySplit[0]);
    int usrCount = std::stoi(bodySplit[1]);
    std::vector<User> usrs;

    for( int i = 0; i < usrCount; ++i) usrs.push_back(User(std::stoi(bodySplit[i+2])));

    if ( repo.addUsersToChat(chat, usrs) ) response.statusCode = OK;
    else response.statusCode = BadRequest;

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
bool JoinChatRoom::CanHandle(Request request){
    return request.target == REQUESTED_TARGET;
};

Response JoinChatRoom::Handle(Request request){
    Response response;
    response.statusCode = OK;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.cookie = request.cookie;
    response.body = "";

    std::vector<std::string> bodySplit = split(request.body);
    ChatRepo repo(connections);

    ChatRoom chat(std::stoi(bodySplit[0]));
    User usr(std::stoi(bodySplit[1]));
    if( chat.getId() < 1 || usr.Id < 1 ){
        response.statusCode = BadRequest;
        return response;
    };

    std::vector<User> usrs;
    usrs.push_back(usr);

    if ( repo.addUsersToChat(chat, usrs) ) response.statusCode = OK;
    else response.statusCode = BadRequest;

    return response;
};

std::vector<std::string> JoinChatRoom::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        elems.push_back(item);
    }
    return elems;
}
//end of JoinChatRoom

//FindChatRoom
bool FindChatRoom::CanHandle(Request request){
    return request.target == REQUESTED_TARGET;
};

Response FindChatRoom::Handle(Request request){
    Response response;
    response.statusCode = OK;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.cookie = request.cookie;
    response.body = "";
    std::vector<std::string> bodySplit = split(request.body);
    ChatRepo repo(connections);
    if( bodySplit.size() != 1){
        response.statusCode = BadRequest;
        return response;
    };
    if( bodySplit[0] == ""){
        response.statusCode = BadRequest;
        return response;
    };

    std::vector<ChatRoom> chats = repo.findByName(bodySplit[0]);
    for( int i = 0; i < chats.size(); ++i ) {
        response.body += std::to_string(chats[i].getId()) + " " + chats[i].getName() + "\n";
    }

    response.statusCode = OK;
    return response;
};

std::vector<std::string> FindChatRoom::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        elems.push_back(item);
    }
    return elems;
}
