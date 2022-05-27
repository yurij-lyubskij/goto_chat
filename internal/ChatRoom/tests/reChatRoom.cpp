#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "reChatRoom.h"
#include "ChatRoom.h"
#include "../WebSocketServer/tests/reWebSocketServer.h"

//TEST(ChatTests, adding){
//	ChatRoom chat(1);
//	User usr;
//	usr.Id = 1;
//	usr.Name = "abc";
//	usr.PhoneNumber = "1234567890";
//	chat.addUser(usr);
//	std::vector<User> mems = chat.getMembers();
//	EXPECT_EQ(mems.size(), 1);
//	EXPECT_EQ(mems[0].Id, 1);
//	EXPECT_EQ(mems[0].Name, "abc");
//	EXPECT_EQ(mems[0].PhoneNumber, "1234567890");
//}

//TEST(ChatTests, removing){
//	ChatRoom chat(1);
//	User usr;
//	usr.Id = 1;
//	usr.Name = "abc";
//	usr.PhoneNumber = "1234567890";
//	chat.addUser(usr);
//	chat.removeUser(usr);
//	std::vector<User> mems = chat.getMembers();
//	EXPECT_EQ(mems.size(), 0);
//}
//
//TEST(ChatTests, reaction){
//	reWebSocketServer serv;
//	ChatRoom chat(1);
//	User usr;
//	Message mes("abc", usr);
//
//	EXPECT_CALL(serv, addToQueue(testing::_)).Times(1);
//
//	EXPECT_EQ(chat.reactOn(mes), true);
//}