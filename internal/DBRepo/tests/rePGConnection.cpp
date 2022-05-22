#include <time.h>

#include "reDBConnection.h"

TEST(PGConnectionTests, checkUsers) {
    PGConnection conn;

	User user1(0);
	user1.Name = "checkUserTest";
	user1.PhoneNumber = "1234567890";
	std::vector<DBObject> users;

	users.push_back(user1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_NE(users[0].attr[0], "0");
	User usr(users[0]);
	++usr.Id;
	users[0] = usr;

	request.operation = checkIt;
	users = conn.exec(request, users);
	EXPECT_EQ(users.size(), 0);
	--usr.Id;
	users.push_back(usr);
	users = conn.exec(request, users);
	EXPECT_EQ(users.size(), 1);
}

TEST(PGConnectionTests, checkChats) {
    PGConnection conn;

	ChatRoom chat1("checChatTest");
	std::vector<DBObject> chats;

	chats.push_back(chat1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = chat;
	request.request = "";
	chats = conn.exec(request, chats);
	ASSERT_NE(chats[0].attr[0], "0");
	chat1 = chats[0];
	ChatRoom chat2(0);

	request.operation = checkIt;
	chats[0] = chat2;
	chats = conn.exec(request, chats);
	EXPECT_EQ(chats.size(), 0);

	chats.push_back(chat1);
	chats = conn.exec(request, chats);
	EXPECT_EQ(chats.size(), 1);
}

TEST(PGConnectionTests, checkMessages) {
    PGConnection conn;
ChatRoom chat1("checkMessagesTest");
	User user1(0);
	user1.Name = "checkMessagesTest";
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
	chat1 = chats[0];

	Message mes1("checkMessagesTest", std::time(NULL), usr.Id, chat1.getId());

	messages.push_back(mes1);

	request.objectType = message;
	messages = conn.exec(request, messages);
	ASSERT_EQ(messages.size(), 1);
	mes1 = (iMessage) messages[0];
	Message mes2(0, mes1.getContent(), mes1.getTime(), mes1.getSender(), mes1.getChat());

	request.operation = checkIt;
	messages[0] = mes2;
	messages = conn.exec(request, messages);
	EXPECT_EQ(messages.size(), 0);

	messages.push_back(mes1);
	messages = conn.exec(request, messages);
	EXPECT_EQ(messages.size(), 1);
}

TEST(PGConnectionTests, putUsers) {
    PGConnection conn;
	User user1(0), user2(0);
	std::vector<DBObject> users;
	user1.Name = "putUsersTest1";
	user1.PhoneNumber = "1234567890";

	user2.Name = "putUsersTest2";
	user2.PhoneNumber = "2134567890";

	users.push_back(user1);
	users.push_back(user2);

	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";

	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 2);

	User usr1(users[0]), usr2(users[1]);
	
	EXPECT_EQ(usr1.Name, "putUsersTest1");
	EXPECT_EQ(usr1.PhoneNumber, "1234567890");
	EXPECT_EQ(usr2.Name, "putUsersTest2");
	EXPECT_EQ(usr2.PhoneNumber, "2134567890");
}

TEST(PGConnectionTests, putChats) {
    PGConnection conn;
	ChatRoom chat1("putChatTest1"), chat2("putChatTest2");
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
	EXPECT_NE(chat1.getId(), 0);
	EXPECT_EQ(chat1.getName(), "putChatTest1");
	EXPECT_NE(chat2.getId(), 0);
	EXPECT_EQ(chat2.getName(), "putChatTest2");
}

TEST(PGConnectionTests, putMessages) {
    PGConnection conn;
	ChatRoom chat1("putMessagesTest");
	User user1(0);
	user1.Name = "putMessagesTest";
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
	chat1 = chats[0];

	Message mes1("putMessagesTest", std::time(NULL), usr.Id, chat1.getId());
	VoiceMessage mes2("/put/Messages/Test", std::time(NULL), usr.Id, chat1.getId());

	messages.push_back(mes1);
	messages.push_back(mes2);

	request.objectType = message;
	messages = conn.exec(request, messages);
	ASSERT_EQ(messages.size(), 2);

	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];
	time_t sendTime = std::time(NULL);

	EXPECT_EQ(mes1.getContent(), "putMessagesTest");
	EXPECT_EQ(mes1.getTime(), sendTime);
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());

	EXPECT_EQ(mes2.getContent(), "/put/Messages/Test");
	EXPECT_EQ(mes2.getTime(), sendTime);
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());
}