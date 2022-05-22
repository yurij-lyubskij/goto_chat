#include "reDBConnection.h"

TEST(PGConnectionTest, putUsers) {
    PGConnection conn;
	User user1(0), user2(0);
	std::vector<DBObject> users;
	user1.Name = "abc";
	user1.PhoneNumber = "1234567890";

	user2.Name = "abcd";
	user2.PhoneNumber = "1234567890";

	users.push_back(user1);
	users.push_back(user2);

	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";

	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 2);

	User usr1(users[0]), usr2(users[1]);
	
	EXPECT_EQ(usr1.Name, "abc");
	EXPECT_EQ(usr1.PhoneNumber, "1234567890");
	EXPECT_EQ(usr2.Name, "abcd");
	EXPECT_EQ(usr2.PhoneNumber, "1234567890");
}

TEST(PGConnectionTest, putChats) {
    PGConnection conn;
	ChatRoom chat1("chat1"), chat2("chat2");
	std::vector<DBObject> chats;

	chats.push_back(chat1);
	chats.push_back(chat2);

	DBRequest request;
	request.operation = putIt;
	request.objectType = chat;
	request.request = "";

	chats = conn.exec(request, chats);
	ASSERT_EQ(chats.size(), 2);

	chat1 = chats[0];
	chat2 = chats[1];

	EXPECT_EQ(chat1.getName(), "chat1");
	EXPECT_EQ(chat2.getName(), "chat2");
}

TEST(PGConnectionTest, putMessages) {
    PGConnection conn;
	ChatRoom chat1("chat1");
	User user1(0);
	user1.Name = "user";
	user1.PhoneNumber = "1234567890";
	std::vector<DBObject> users, chats, messages;

	users.push_back(user1);
	chats.push_back(chat1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_NE(users[0].attr[0], "0");
	User usr(users[0]);

	request.objectType = chat;
	chats = conn.exec(request, chats);
	ASSERT_NE(chats[0].attr[0], "0");

	Message mes1("Content", 12, usr.Id, chat1.getId());
	VoiceMessage mes2("path", 13, usr.Id, chat1.getId());

	messages.push_back(mes1);
	messages.push_back(mes2);

	request.objectType = message;
	messages = conn.exec(request, messages);
	ASSERT_EQ(messages.size(), 2);

	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];

	EXPECT_EQ(mes1.getContent(), "Content");
	EXPECT_EQ(mes1.getTime(), 12);
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());

	EXPECT_EQ(mes2.getContent(), "path");
	EXPECT_EQ(mes2.getTime(), 13);
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());

}