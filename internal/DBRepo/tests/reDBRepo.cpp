#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "User.h"
#include "reDBRepo.h"
#include "reDBConnection.h"
/*
//
//UserRepo Section
//
TEST(UserRepoTests, DoesExist){
	MockConnection conn;
	EXPECT_CALL(conn, exec(::testing::_, ::testing::_)).Times(3);

	UserRepo repo;
	EXPECT_FALSE(repo.doesExist(1));

	User usr;
	usr.Id = 1;
	usr.Name = "abc";
	usr.PhoneNumber = "1234567890";
	std::vector<User> users;
	users.push_back(usr);

	repo.put(users);
	EXPECT_TRUE(repo.doesExist(1));
}

TEST(UserRepoTests, putAndgetById){
	MockConnection conn;
	EXPECT_CALL(conn, get(::testing::_)).Times(2);

	UserRepo repo;
	User usr1, usr2;
	usr1.Id = 1;						usr1.Id = 2;
	usr1.Name = "abc";					usr1.Name = "abc";								
	usr2.PhoneNumber = "1234567890";	usr1.PhoneNumber = "1023456789";

	std::vector<User> users;
	users.push_back(usr1);
	users.push_back(usr2);

	std::vector<int> ids = { 1 , 2};

	repo.put(users);
	users = repo.getByID(ids);
	EXPECT_EQ(users[0].Id, usr1.Id);
	EXPECT_EQ(users[1].Id, usr2.Id);
}

//
//end of UserRepo Section
//
*/

//
//ChatRepo Section
//
TEST(ChatRepoTests, DoesExist){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(3);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	EXPECT_FALSE(repo.doesExist(1));
 
	ChatRoom chat("name");
	std::vector<ChatRoom> chats;
	chats.push_back(chat);
	EXPECT_TRUE(repo.put(chats));
	EXPECT_TRUE(repo.doesExist(1));
}

TEST(ChatRepoTests, putAndgetById){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);

	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(1);
	EXPECT_CALL(*conn, reGet(::testing::_)).Times(1);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	ChatRoom chat1("test"), chat2("test");
	std::vector<ChatRoom> chats;

	chats.push_back(chat1);
	chats.push_back(chat2);

	std::vector<int> ids = { 1 , 2 };

	EXPECT_TRUE(repo.put(chats));
	chats = repo.getByID(ids);
	
	ASSERT_EQ(chats.size(), 2);
	EXPECT_EQ(chats[0].getId(), chat1.getId());
	EXPECT_EQ(chats[1].getId(), chat2.getId());
}

//
//end of ChatRepo Section
//

//
//MessageRepo Section
//
TEST(MessageRepoTests, DoesExist){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(3);
	MessageRepo repo((DBConnection<iConnection>*) connections.get());

	EXPECT_FALSE(repo.doesExist(1));

	Message message("text", 50, 1);
	std::vector<iMessage> messages;
	messages.push_back(message);

	EXPECT_TRUE(repo.put(messages));
	EXPECT_TRUE(repo.doesExist(1));
}

TEST(MessageRepoTests, putAndgetById){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(1);
	EXPECT_CALL(*conn, reGet(::testing::_)).Times(1);
	MessageRepo repo((DBConnection<iConnection>*) connections.get());

	Message message1("text1", 12, 1), message2("text2", 50, 2);
	std::vector<iMessage> messages;
	messages.push_back(message1);
	messages.push_back(message2);

	std::vector<int> ids = { 1 , 2 };

	EXPECT_TRUE(repo.put(messages));
	messages = repo.getByID(ids);

	ASSERT_EQ(messages.size(), 2);

	EXPECT_EQ(messages[0].getId(), message1.getId());
	EXPECT_EQ(messages[0].getContent(), message1.getContent());
	EXPECT_EQ(messages[0].getTime(), message1.getTime());
	EXPECT_EQ(messages[0].getSender(), message1.getSender());
	
	EXPECT_EQ(messages[1].getId(), message2.getId());
	EXPECT_EQ(messages[1].getContent(), message2.getContent());
	EXPECT_EQ(messages[1].getTime(), message2.getTime());
	EXPECT_EQ(messages[1].getSender(), message2.getSender());
}

//
//end of MessageRepo Section
//