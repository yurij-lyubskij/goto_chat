#include <time.h>

#include "reDBConnection.h"

TEST(PGConnectionTests, UsersDBTests) {
    PGConnection conn;

	time_t num2 = time(NULL)%1000;
	time_t num1 = num2%100;
	User user1(0), user2(0);
	user1.Name = "UsersDBTests1";
	user1.PhoneNumber = std::to_string(num1);
	user1.password = "testPassword";

	user2.Name = "UsersDBTests2";
	user2.PhoneNumber = std::to_string(num2);
	user2.password = "testPassword";

	std::vector<DBObject> users;

	users.push_back(user1);
	users.push_back(user2);
	
	DBRequest request;
	//Put test
	request.operation = putIt;
	request.objectType = user;
	request.request = "";

	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 2);

	User usr1(users[0]), usr2(users[1]);
	EXPECT_NE(usr1.Id, 0);
	EXPECT_EQ(usr1.Name, "UsersDBTests1");
	EXPECT_EQ(usr1.PhoneNumber, std::to_string(num1));
	EXPECT_EQ(usr1.password, "testPassword");

	EXPECT_NE(usr2.Id, 0);
	EXPECT_EQ(usr2.Name, "UsersDBTests2");
	EXPECT_EQ(usr2.PhoneNumber, std::to_string(num2));
	EXPECT_EQ(usr2.password, "testPassword");

	//check test
	std::vector<DBObject> checkUsers;
	User usr(users[0]);
	int id = usr.Id;
	usr.Id = 0;
	checkUsers.push_back(usr);
	request.operation = checkIt;
	checkUsers = conn.exec(request, checkUsers);
	EXPECT_EQ(checkUsers.size(), 0);
	usr.Id = id;
	checkUsers.push_back(usr);
	checkUsers = conn.exec(request, checkUsers);
	EXPECT_EQ(checkUsers.size(), 1);

	//get test
	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: users) request.request += " " + obj.attr[0];

	users = conn.get(request);
	ASSERT_EQ(users.size(), 2);

	User user3(users[0]), user4(users[1]);
	EXPECT_EQ(user3.Name, "UsersDBTests1");
	EXPECT_EQ(user3.PhoneNumber, std::to_string(num1));
	EXPECT_EQ(user3.password, "testPassword");
	EXPECT_EQ(user4.Name, "UsersDBTests2");
	EXPECT_EQ(user4.PhoneNumber, std::to_string(num2));
	EXPECT_EQ(user4.password, "testPassword");
}

TEST(PGConnectionTests, ChatsDBTests) {
    PGConnection conn;

	ChatRoom chat1("ChatsDBTests1"), chat2("ChatsDBTests2");
	std::vector<DBObject> chats;

	chats.push_back(chat1);
	chats.push_back(chat2);
	
	DBRequest request;
	//put test
	request.operation = putIt;
	request.objectType = chat;
	request.request = "";

	chats = conn.exec(request, chats);
	ASSERT_EQ(chats.size(), 2);
	chat1 = chats[0];
	chat2 = chats[1];
	EXPECT_NE(chat1.getId(), 0);
	EXPECT_EQ(chat1.getName(), "ChatsDBTests1");

	EXPECT_NE(chat2.getId(), 0);
	EXPECT_EQ(chat2.getName(), "ChatsDBTests2");

	//check test
	std::vector<DBObject> checkChats;
	chat1 = chats[0];
	chat2 = ChatRoom(0);

	request.operation = checkIt;
	checkChats.push_back(chat2);
	checkChats = conn.exec(request, checkChats);
	EXPECT_EQ(checkChats.size(), 0);

	checkChats.push_back(chat1);
	checkChats = conn.exec(request, checkChats);
	EXPECT_EQ(checkChats.size(), 1);

	//get test
	std::vector<DBObject> existedChats = chats;
	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: chats) request.request += " " + obj.attr[0];
	chats = conn.get(request);

	ASSERT_EQ(chats.size(), 2);
	chat1 = chats[0];
	chat2 = chats[1];
	ChatRoom exChat1(existedChats[0]), exChat2(existedChats[1]);
	EXPECT_EQ(chat1.getId(), exChat1.getId());
	EXPECT_EQ(chat1.getName(), "ChatsDBTests1");

	EXPECT_EQ(chat2.getId(), exChat2.getId());
	EXPECT_EQ(chat2.getName(), "ChatsDBTests2");

	//addMembers test
	time_t num2 = time(NULL)%100000;
	time_t num1 = num2%10000;
	User user1(0), user2(0);
	user1.Name = "ChatsDBTests1";
	user1.PhoneNumber = std::to_string(num1);
	user1.password = "testPassword";

	user2.Name = "ChatsDBTests2";
	user2.PhoneNumber = std::to_string(num2);
	user2.password = "testPassword";

	std::vector<DBObject> users;

	users.push_back(user1);
	users.push_back(user2);

	request.operation = putIt;
	request.objectType = user;
	request.request = "";

	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 2);

	std::vector<DBObject> chatAndUsers;
	chatAndUsers.push_back(chats[0]);
	chatAndUsers.push_back(users[0]);
	chatAndUsers.push_back(users[1]);
	request.operation = addMembers;
	request.objectType = chat;
	chatAndUsers = conn.exec(request, chatAndUsers);
	ASSERT_NE(chatAndUsers.size(), 0);

	//get with name test
	request.operation = findWithName;
	request.request = "DBTests";
	chats = conn.get(request);

	ASSERT_GE(chats.size(), 2);
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 2]).getId(), chat1.getId());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 2]).getName(), chat1.getName());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 1]).getId(), chat2.getId());
	EXPECT_EQ(((ChatRoom) chats[chats.size() - 1]).getName(), chat2.getName());
}

TEST(PGConnectionTests, MessagesDBTests) {
    PGConnection conn;
	ChatRoom chat1("MessagesDBTests");
	User user1(0);
	user1.Name = "MessagesDBTests";
	user1.PhoneNumber = std::to_string(time(NULL)%1000000);
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

	//put tests
	Message mes1("MessagesDBTests", std::time(NULL), usr.Id, chat1.getId());
	VoiceMessage mes2("/Messages/DB/Tests", std::time(NULL), usr.Id, chat1.getId());

	messages.push_back(mes1);
	messages.push_back(mes2);

	request.objectType = message;
	messages = conn.exec(request, messages);
	time_t sendTime = std::time(NULL);
	ASSERT_EQ(messages.size(), 2);

	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];
	
	EXPECT_EQ(mes1.getContent(), "MessagesDBTests");
	EXPECT_EQ(mes1.getTime(), sendTime);
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());

	EXPECT_EQ(mes2.getContent(), "/Messages/DB/Tests");
	EXPECT_EQ(mes2.getTime(), sendTime);
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());

	//check tests
	std::vector<DBObject> checkMessages;
	
	request.operation = checkIt;
	checkMessages.push_back(Message(0, mes1.getContent(), mes1.getTime(), mes1.getSender(), mes1.getChat()));
	checkMessages = conn.exec(request, checkMessages);
	EXPECT_EQ(checkMessages.size(), 0);

	checkMessages.push_back(mes1);
	checkMessages = conn.exec(request, checkMessages);
	EXPECT_EQ(checkMessages.size(), 1);

	//get tests
	request.operation = getFew;
	request.request = "id";
	for(DBObject obj: messages) request.request += " " + obj.attr[0];

	messages = conn.get(request);
	ASSERT_EQ(messages.size(), 2);
	Message mes3 = (iMessage) messages[0];
	VoiceMessage mes4 = (iMessage) messages[1];
	EXPECT_EQ(mes3.getId(), mes1.getId());
	EXPECT_EQ(mes3.getContent(), "MessagesDBTests");
	EXPECT_EQ(mes3.getTime(), sendTime);
	EXPECT_EQ(mes3.getSender(), usr.Id);
	EXPECT_EQ(mes3.getChat(), chat1.getId());

	EXPECT_EQ(mes4.getId(), mes2.getId());
	EXPECT_EQ(mes4.getContent(), "/Messages/DB/Tests");
	EXPECT_EQ(mes4.getTime(), sendTime);
	EXPECT_EQ(mes4.getSender(), usr.Id);
	EXPECT_EQ(mes4.getChat(), chat1.getId());

	//get from range test
	request.operation = getRange;
	request.request = std::to_string(chat1.getId()) + " 1 2";
	messages = conn.get(request);
	ASSERT_EQ(messages.size(), 2);
	mes1 = (iMessage) messages[0];
	mes2 = (iMessage) messages[1];

	EXPECT_EQ(mes1.getContent(), "MessagesDBTests");
	EXPECT_EQ(mes1.getSender(), usr.Id);
	EXPECT_EQ(mes1.getChat(), chat1.getId());
	EXPECT_EQ(mes2.getContent(), "/Messages/DB/Tests");
	EXPECT_EQ(mes2.getSender(), usr.Id);
	EXPECT_EQ(mes2.getChat(), chat1.getId());
}
