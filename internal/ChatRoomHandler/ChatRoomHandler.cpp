#include <sstream>
#include <vector>


#include "ChatRoomHandler.h"
#include "ChatRoom.h"
#include "Handler.h"
#include "Request.h"
#include "Response.h"
#include "DBRepo.h"
#include "rapidjson/writer.h"

#include "rapidjson/document.h"

#include "rapidjson/stringbuffer.h"

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
    
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = BadRequest;

    jsonParser parser;

    ChatRepo repo(connections);
    ChatRoom newChat;

    rapidjson::Document d;
    const char* json = request.body.c_str();
    d.Parse(json);
    if(! d.HasMember("chatName")) return response;
    newChat = ChatRoom(d["chatName"].GetString());

    int usersCount = 0;
    if(! d.HasMember("usersCount")) return response;
    usersCount = d["usersCount"].GetInt();

    if(! d.HasMember("users")) return response;
    if(! d["users"].IsArray()) return response;
    std::vector<User> usrs;
    const rapidjson::Value& usersId = d["users"];
    for (rapidjson::SizeType i = 0; i < usersId.Size(); i++)
        usrs.push_back(User(usersId[i].GetInt()));

    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";

    std::vector<ChatRoom> chats;
    chats.push_back(newChat);
    std::vector<int> res = repo.put(chats);
    if( res.empty() ){
        response.statusCode = BadRequest;
        return response;
    };
    response.body = "{\"chatId\":" + std::to_string(res[0]) + "}'";
    if ( repo.addUsersToChat(res[0], usrs) ) response.statusCode = OK;
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
