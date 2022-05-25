#include <sstream>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>
#include <string>
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
    return boost::starts_with(request.target, REQUESTED_TARGET);
};

Response GetMessageFromChat::Handle(Request request){
    Response response;
    response.statusCode = OK;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }

    MessageRepo repo(connections);
    
    std::vector<std::string> params = split(request.target.substr(REQUESTED_TARGET.size(), request.target.size() - 1), '&');
    std::string chatId;
    int start;
    int end;
    {
        const std::string beginning = "/?from=";
        if (! boost::starts_with(params[0], beginning))  return response;
        chatId = params[0].substr(beginning.size(), params.size() - 1);
    }
    /*
    {
        const std::string beginning = "/?from=";
        if (! boost::starts_with(params, beginning))  return response;
        chatId = params[0].substr(beginning.size(), params.size() - 1);
    }
    */
   
   /*
    response.cookie = request.cookie;
    response.body = "";
    std::vector<std::string> bodySplit = split(request.body);
    


    if( bodySplit.size() != 4 ){
        response.statusCode = BadRequest;
        return response;
    };
    int start = std::stoi(bodySplit[2]);
    int end = std::stoi(bodySplit[2]) + std::stoi(bodySplit[3]) - 1;


*/
    std::vector<iMessage> messages = repo.getFromRange(start, end, ChatRoom(std::stoi(chatId)));
    int len = messages.size();
    response.body += "{";
    response.body += "\"messagesCount\":\"";
    response.body += std::to_string(len);
    response.body += "\",";
    response.body += "\"messages\":";

    response.body += "[";
    response.body += "{";
    response.body += "\"id\":\"";
    response.body += std::to_string(messages[0].getId());
    response.body += "\",";
    response.body += "\"text\":\"";
    response.body += messages[0].getContent();
    response.body += "\"time\":\"";
    response.body += std::to_string(messages[0].getTime());
    response.body += "\"}";
    for( int i = 1; i < len; ++i ) {
        response.body += ",{";
         response.body += "\"id\":\"";
    response.body += std::to_string(messages[i].getId());
    response.body += "\",";
    response.body += "\"text\":\"";
    response.body += messages[i].getContent();
    response.body += "\"time\":\"";
    response.body += std::to_string(messages[i].getTime());
    response.body += "\"}";
    }
    response.body += "]}";

    response.statusCode = OK;
    return response;
};

std::vector<std::string> GetMessageFromChat::split(const std::string &s, char c) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, c)) {
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
    UserRepo usRepo(connections);
    ChatRoom newChat;

    rapidjson::Document d;
    const char* json = request.body.c_str();
    d.Parse(json);
    if(! d.HasMember("chatName")) return response;
    newChat = ChatRoom(d["chatName"].GetString());
    /*
    int usersCount = 0;
    if(! d.HasMember("usersCount")) return response;
    usersCount = d["usersCount"].GetInt();
    */
    if(! d.HasMember("users")) return response;
    if(! d["users"].IsArray()) return response;
    std::vector<std::string> usersPhones;
    const rapidjson::Value& usersPh = d["users"];
    User usr;
    usr.Id = 0;
    usr.Name = "";
    usr.password = "";
    std::vector<User> usrs;
    for (rapidjson::SizeType i = 0; i < usersPh.Size(); i++){
        usersPhones.push_back(usersPh[i].GetString());
        usrs.push_back(usRepo.GetbyPhone(usersPh[i].GetString()));
    }
    if(usrs.empty()) {
        response.statusCode = NotFound;
        return response;
    }
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
    response.body = "{\"chatId\":" + std::to_string(res[0]) + "}";
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
    
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = BadRequest;

    jsonParser parser;

    ChatRepo repo(connections);
    UserRepo usRepo(connections);
    ChatRoom joinedChat;

    rapidjson::Document d;
    const char* json = request.body.c_str();
    d.Parse(json);
    if(! d.HasMember("chatId")) return response;
    joinedChat = ChatRoom(std::stoi(d["chatId"].GetString()));

    if(! d.HasMember("user")) return response;
    std::vector<User> usrs;
    usrs.push_back(usRepo.GetbyPhone(d["user"].GetString()));
    
    if (! repo.doesExist(joinedChat.getId())){
        response.statusCode = NotFound;
        return response;
    }

    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";

    if ( repo.addUsersToChat(joinedChat, usrs) ) response.statusCode = OK;
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
    return boost::starts_with(request.target, REQUESTED_TARGET);
};

Response FindChatRoom::Handle(Request request){
    Response response;
    
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = BadRequest;

    ChatRepo repo(connections);
    ChatRoom joinedChat;

    std::string params = request.target.substr(REQUESTED_TARGET.size(), request.target.size() - 1);

    const std::string beginning = "/?name=";
    if (! boost::starts_with(params, beginning))  return response;
    std::string chatName = params.substr(beginning.size(), params.size() - 1);


    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";

    std::vector<ChatRoom> chats = repo.findByName(chatName);
    int len = chats.size();
    response.body += "{";
    response.body += "\"chatCount\":\"";
    response.body += std::to_string(len);
    response.body += "\",";
    response.body += "\"chats\":";

    response.body += "[";
    response.body += "{";
    response.body += "\"id\":\"";
    response.body += std::to_string(chats[0].getId());
    response.body += "\",";
    response.body += "\"chatName\":\"";
    response.body += chats[0].getName();
     response.body += "\"}";
    for( int i = 1; i < len; ++i ) {
        response.body += ",{";
        response.body += "\"id\":\"";
        response.body += std::to_string(chats[i].getId());
        response.body += "\",";
        response.body += "\"chatName\":\"";
        response.body += chats[i].getName();
        response.body += "\"}";
    }
    response.body += "]}";

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
