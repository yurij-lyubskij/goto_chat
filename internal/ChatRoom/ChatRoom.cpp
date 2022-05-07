#include "ChatRoom.h"
#include "DBRepo.h"


ChatRoom::ChatRoom(){ id = 0; };

ChatRoom::ChatRoom(int _id){ id = _id; };

ChatRoom::ChatRoom(int _id, std::string _name){
	id = _id;
	name = _name;
};
ChatRoom::ChatRoom(const ChatRoom& cht){
	id = cht.id;
	name = cht.name;
};

bool ChatRoom::reactOn(Message mes){
	return true;
}

ChatRoom ChatRoom::operator=(const ChatRoom& cht){
	return ChatRoom(cht);
};
