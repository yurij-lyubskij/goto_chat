#include <time.h>

#include "reDBConnection.h"

TEST(PGConnectionTests, checkUsers) {
    PGConnection conn;
	User user1(0);
	user1.Name = "checkUserTest";
	user1.PhoneNumber = std::to_string(time(NULL)%10);
	user1.password = "testPassword";
	std::vector<DBObject> users;

	users.push_back(user1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 1);
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

	ChatRoom chat1("checkChatTest");
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
	user1.PhoneNumber = std::to_string(time(NULL)%100);
	user1.password = "testPassword";
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
	time_t num1 = time(NULL)%1000;
	time_t num2 = time(NULL)%10000;
	User user1(0), user2(0);
	std::vector<DBObject> users;
	user1.Name = "putUsersTest1";
	user1.PhoneNumber = std::to_string(num1);
	user1.password = "testPassword";

	user2.Name = "putUsersTest2";
	user2.PhoneNumber = std::to_string(num2);
	user2.password = "testPassword";

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
	EXPECT_EQ(usr1.PhoneNumber, std::to_string(num1));
	EXPECT_EQ(usr1.password, "testPassword");
	EXPECT_EQ(usr2.Name, "putUsersTest2");
	EXPECT_EQ(usr2.password, "testPassword");
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
	user1.PhoneNumber = std::to_string(time(NULL)%100000);
	user1.password = "testPassword";
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

TEST(PGConnectionTests, addMembersTest) {
    PGConnection conn;
	ChatRoom chat1("addMembersTest");
	User user1(0);
	user1.Name = "addMembersTest";
	user1.PhoneNumber = std::to_string(time(NULL)%1000000);
	user1.password = "testPassword";
	std::vector<DBObject> users, chats, chatAndUsers;

	users.push_back(user1);
	chats.push_back(chat1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_NE(users[0].attr[0], "0");

	request.objectType = chat;
	chats = conn.exec(request, chats);
	ASSERT_NE(chats[0].attr[0], "0");
	chatAndUsers.push_back(chats[0]);
	chatAndUsers.push_back(users[0]);

	request.operation = addMembers;
	request.objectType = message;
	chatAndUsers = conn.exec(request, chatAndUsers);
	ASSERT_NE(chatAndUsers.size(), 0);
}

TEST(PGConnectionTests, getUsers) {
    PGConnection conn;
	time_t num = time(NULL)%10000000;
	User user1(0);
	user1.Name = "getUserTest";
	user1.PhoneNumber = std::to_string(num);
	user1.password = "testPassword";
	std::vector<DBObject> users;

	users.push_back(user1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_NE(users[0].attr[0], "0");

	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: users) request.request += " " + obj.attr[0];
	users = conn.get(request);

	ASSERT_EQ(users.size(), 1);
	User user2(users[0]);
	EXPECT_EQ(user2.Name, "getUserTest");
	EXPECT_EQ(user2.PhoneNumber, std::to_string(num));
	EXPECT_EQ(user2.password, "testPassword");
}

TEST(PGConnectionTests, getChats) {
    PGConnection conn;
	ChatRoom chat1("getChatTest");
	std::vector<DBObject> chats;

	chats.push_back(chat1);

	DBRequest request;
	request.operation = putIt;
	request.objectType = chat;
	request.request = "";

	chats = conn.exec(request, chats);
	ASSERT_EQ(chats.size(), 1);

	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: chats) request.request += " " + obj.attr[0];
	chats = conn.get(request);

	ASSERT_EQ(chats.size(), 1);
	chat1 = chats[0];
	EXPECT_NE(chat1.getId(), 0);
	EXPECT_EQ(chat1.getName(), "getChatTest");
}

TEST(PGConnectionTests, getMessages) {
    PGConnection conn;
	ChatRoom chat1("getMessagesTest");
	User user1(0);
	user1.Name = "getMessagesTest";
	user1.PhoneNumber = std::to_string(time(NULL)%100000000);
	user1.password = "testPassword";
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

	Message mes1("getMessagesTest", std::time(NULL), usr.Id, chat1.getId());
	VoiceMessage mes2("/get/Messages/Test", std::time(NULL), usr.Id, chat1.getId());

	messages.push_back(mes1);
	messages.push_back(mes2);

	request.objectType = message;
	messages = conn.exec(request, messages);
	ASSERT_EQ(messages.size(), 2);

	time_t sendTime = std::time(NULL);

	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: messages) request.request += " " + obj.attr[0];

	messages = conn.get(request);
	ASSERT_EQ(messages.size(), 2);
	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];
	EXPECT_EQ(mes1.getContent(), "getMessagesTest");
	EXPECT_EQ(mes1.getTime(), sendTime);
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());

	EXPECT_EQ(mes2.getContent(), "/get/Messages/Test");
	EXPECT_EQ(mes2.getTime(), sendTime);
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());
}

TEST(PGConnectionTests, getChatsByName) {
    PGConnection conn;
	ChatRoom chat1("getChatsByName1"), chat2("getChatsByName2");
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

	request.operation = findWithName;
	request.request = "ChatsByName";
	chats = conn.get(request);

	ASSERT_GE(chats.size(), 2);
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 2]).getId(), chat1.getId());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 2]).getName(), chat1.getName());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 1]).getId(), chat2.getId());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 1]).getName(), chat2.getName());
}

TEST(PGConnectionTests, getMessagesFromRange) {
PGConnection conn;
	ChatRoom chat1("getFromRange");
	User user1(0);
	user1.Name = "getFromRange";
	user1.PhoneNumber = std::to_string(time(NULL)%1000000000);
	user1.password = "testPassword";
	std::vector<DBObject> users, chats, messages;

	users.push_back(user1);
	chats.push_back(chat1);
	
	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";
	users = conn.exec(request, users);
	ASSERT_NE(users.size(), 0);
	User usr(users[0]);

	request.objectType = chat;
	chats = conn.exec(request, chats);
	ASSERT_NE(chats.size(), 0);
	chat1 = chats[0];

	Message mes1("getFromRange", std::time(NULL), usr.Id, chat1.getId());
	VoiceMessage mes2("/get/From/Range", std::time(NULL), usr.Id, chat1.getId());

	messages.push_back(mes1);
	messages.push_back(mes2);

	request.objectType = message;
	messages = conn.exec(request, messages);
	ASSERT_EQ(messages.size(), 2);

	request.operation = getRange;
	request.request = std::to_string(chat1.getId()) + " 1 2";
	messages = conn.get(request);
	ASSERT_EQ(messages.size(), 2);
	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];

	EXPECT_EQ(mes1.getContent(), "getFromRange");
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());
	EXPECT_EQ(mes2.getContent(), "/get/From/Range");
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());
}

