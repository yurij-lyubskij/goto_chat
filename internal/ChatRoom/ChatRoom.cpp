#include "ChatRoom.h"
#include "DBRepo.h"


ChatRoom::ChatRoom(){ 
	id = -1; 
	name = "";
};

ChatRoom::ChatRoom(int _id){ 
	id = _id; 
	name = "";
};

ChatRoom::ChatRoom(std::string& _name){
	id = 0;
	name = _name;
};

ChatRoom::ChatRoom(int _id, std::string& _name){
	id = _id;
	name = _name;
};

ChatRoom::ChatRoom(const ChatRoom& cht) : iChatRoom(cht) {
	id = cht.id;
	name = cht.name;
};

ChatRoom& ChatRoom::operator=(const ChatRoom& cht){
	id = cht.id;
	name = cht.name;
	return *this;
};