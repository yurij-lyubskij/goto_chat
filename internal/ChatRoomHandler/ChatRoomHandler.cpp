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
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = BadRequest;

    MessageRepo mesRepo(connections);
    UserRepo usRepo(connections);
    std::string params = request.target.substr(REQUESTED_TARGET.size(), request.target.size() - 1);
    std::string beginning = "/?mes=";
    std::vector<iMessage> messages;

    if ( boost::starts_with(params, beginning)){
        std::vector<std::string> parametrs = split(params, '&');
        if(parametrs.size() != 2) return response;

        std::string mesId = parametrs[0].substr(beginning.size(), parametrs[0].size() - 1);

        beginning = "mode=";
        if (! boost::starts_with(parametrs[1], beginning)) return response;
        if (parametrs[1].substr(beginning.size(), parametrs[1].size() - 1)[0] == '0') messages = mesRepo.getNextFew(std::stoi(mesId), 20);
        else messages = mesRepo.getLastFew(std::stoi(mesId), 20);
    }else{
        beginning = "/?chat=";
        if(! boost::starts_with(params, beginning)) return response;
        std::string chatId = params.substr(beginning.size(), params.size() - 1);
        messages  = mesRepo.getLastFromChat(std::stoi(chatId), 20);
    }

    int len = messages.size();
    if ( len == 0) {
        response.statusCode = NotFound;
        return response;
    }

    jsonParser parser;
    response.body += "{";
    response.body += "\"messagesCount\":\"";
    response.body += std::to_string(len);
    response.body += "\",";
    response.body += "\"messages\":";

    response.body += "[";
    response.body +=  parser.serializeMessage(messages[0], usRepo.GetbyId(messages[0].getSender()));
    for( int i = 1; i < len; ++i ) {
        response.body += ",";
        response.body += parser.serializeMessage(messages[i], usRepo.GetbyId(messages[i].getSender()));
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

    response.statusCode = NotFound;
    User usr;
    usr.Id = 0;
    usr.Name = "";
    usr.password = "";
    std::vector<User> usrs;
    for (rapidjson::SizeType i = 0; i < usersPh.Size(); ++i){
        usersPhones.push_back(usersPh[i].GetString());
        usr = usRepo.GetbyPhone(usersPh[i].GetString());

        if (usr.Id == 0) return response;

        usrs.push_back(usRepo.GetbyPhone(usersPh[i].GetString()));
    }
    
    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";

    std::vector<ChatRoom> chats;
    chats.push_back(newChat);
    std::vector<int> res = repo.put(chats);
    if( res.empty() ) return response;

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

    response.statusCode = NotFound;
    std::vector<User> usrs;
    User usr = usRepo.GetbyPhone(d["user"].GetString());
    if (usr.Id == 0) return response;
    usrs.push_back(usr);
    
    if (! repo.doesExist(joinedChat.getId()))return response;
    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";
    if ( repo.addUsersToChat(joinedChat, usrs) ) response.statusCode = OK;
    else response.statusCode = Conflict;

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


    

    std::vector<ChatRoom> chats = repo.findByName(chatName);
    int len = chats.size();
    if ( len == 0) {
        response.statusCode = NotFound;
        return response;
    }
    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";
    jsonParser parser;
    response.body += "{";
    response.body += "\"chatCount\":\"";
    response.body += std::to_string(len);
    response.body += "\",";
    response.body += "\"chats\":";

    response.body += "[";
    response.body += parser.serializeChat(chats[0]);
    for( int i = 1; i < len; ++i ) {
        response.body += ",";
        response.body += parser.serializeChat(chats[i]);
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
//end of FindChatRoom

//GetUserChats
bool GetUserChats::CanHandle(Request request){
    return boost::starts_with(request.target, REQUESTED_TARGET);
};

Response GetUserChats::Handle(Request request){
    Response response;
    if (request.responseStatus != OK) {
        response.statusCode = UnAuthorized;
        return response;
    }
    response.statusCode = BadRequest;

    ChatRepo chRepo(connections);
    UserRepo usRepo(connections);
    ChatRoom joinedChat;

    std::string params = request.target.substr(REQUESTED_TARGET.size(), request.target.size() - 1);

    const std::string beginning = "/?user=";

    if (! boost::starts_with(params, beginning))  return response;
    response.statusCode = NotFound;

    std::string usPhone = params.substr(beginning.size(), params.size() - 1);
    User user = usRepo.GetbyPhone(usPhone);
    if(user.Id == 0) return response;

    std::vector<ChatRoom> chats = chRepo.getUserChats(user);
    int len = chats.size();
    if ( len == 0)  return response;

    response.statusCode = OK;
    response.cookie = request.cookie;
    response.body = "";
    jsonParser parser;
    response.body += "{";
    response.body += "\"chatCount\":\"";
    response.body += std::to_string(len);
    response.body += "\",";
    response.body += "\"chats\":";

    response.body += "[";
    response.body += parser.serializeChat(chats[0]);
    for( int i = 1; i < len; ++i ) {
        response.body += ",";
        response.body += parser.serializeChat(chats[i]);
    }
    response.body += "]}";

    return response;
};
//end of GetUserChats