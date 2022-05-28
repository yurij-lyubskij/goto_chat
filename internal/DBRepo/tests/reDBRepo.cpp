#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <map>

#include "User.h"
#include "reDBRepo.h"
#include "reDBConnection.h"
/*
//
//UserRepo Section
/*
TEST(UserRepoTests, getById){
=======
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

	conn->chats.insert(std::make_pair(2, ChatRoom(2, "test")));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(2);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	EXPECT_FALSE(repo.doesExist(1));
	EXPECT_TRUE(repo.doesExist(2));
}

TEST(ChatRepoTests, put){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(2);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	ChatRoom chat1("test1"), chat2("test2");
	std::vector<ChatRoom> chats;

	chats.push_back(chat1);
	chats.push_back(chat2);

	EXPECT_THAT(repo.put(chats),  testing::ElementsAre(1, 2));
	EXPECT_THAT(repo.put(chats),  testing::ElementsAre(3, 4));

	ASSERT_TRUE(conn->chats.contains(1));
	EXPECT_EQ(conn->chats.at(1).getId(), 1);
	EXPECT_EQ(conn->chats.at(1).getName(), "test1");
	ASSERT_TRUE(conn->chats.contains(2));
	EXPECT_EQ(conn->chats.at(2).getId(), 2);
	EXPECT_EQ(conn->chats.at(2).getName(), "test2");
	ASSERT_TRUE(conn->chats.contains(3));
	EXPECT_EQ(conn->chats.at(3).getId(), 3);
	EXPECT_EQ(conn->chats.at(3).getName(), "test1");
	ASSERT_TRUE(conn->chats.contains(4));
	EXPECT_EQ(conn->chats.at(4).getId(), 4);
	EXPECT_EQ(conn->chats.at(4).getName(), "test2");
}

TEST(ChatRepoTests, getById){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);

	conn->chats.insert(std::make_pair(1, ChatRoom(1, "test1")));
	conn->chats.insert(std::make_pair(2, ChatRoom(2, "test2")));
	
	EXPECT_CALL(*conn, reGet(::testing::_)).Times(2);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	std::vector<int> ids = { 3 };

	std::vector<ChatRoom> chats = repo.getByID(ids);
	EXPECT_TRUE( chats.empty() );

	ids = { 1, 2 };
	chats = repo.getByID(ids);

	ASSERT_EQ( chats.size(), 2 );
	
	EXPECT_EQ(chats[0].getId(), 1);
	EXPECT_EQ(chats[0].getName(), "test1");
	EXPECT_EQ(chats[1].getId(), 2);
	EXPECT_EQ(chats[1].getName(), "test2");
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
	
	conn->messages.insert(std::make_pair(2, Message(2, "test", 50, 1, 1)));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(2);
	MessageRepo repo((DBConnection<iConnection>*) connections.get());

	EXPECT_FALSE(repo.doesExist(1));
	EXPECT_TRUE(repo.doesExist(2));
}

TEST(MessageRepoTests, put){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(2);
	MessageRepo repo((DBConnection<iConnection>*) connections.get());

	Message message1("text1", 12, 1, 1), message2("text2", 50, 2, 1);
	std::vector<iMessage> messages;
	messages.push_back(message1);
	messages.push_back(message2);

	EXPECT_THAT(repo.put(messages),  testing::ElementsAre(1, 2));
	EXPECT_THAT(repo.put(messages),  testing::ElementsAre(3, 4));

	ASSERT_TRUE(conn->messages.contains(1));
	EXPECT_EQ(conn->messages.at(1).getId(), 1);
	EXPECT_EQ(conn->messages.at(1).getContent(), "text1");
	EXPECT_EQ(conn->messages.at(1).getTime(), 12);
	EXPECT_EQ(conn->messages.at(1).getSender(), 1);
	EXPECT_EQ(conn->messages.at(1).getChat(), 1);

	ASSERT_TRUE(conn->messages.contains(2));
	EXPECT_EQ(conn->messages.at(2).getId(), 2);
	EXPECT_EQ(conn->messages.at(2).getContent(), "text2");
	EXPECT_EQ(conn->messages.at(2).getTime(), 50);
	EXPECT_EQ(conn->messages.at(2).getSender(), 2);
	EXPECT_EQ(conn->messages.at(2).getChat(), 1);

	ASSERT_TRUE(conn->messages.contains(3));
	EXPECT_EQ(conn->messages.at(3).getId(), 3);
	EXPECT_EQ(conn->messages.at(3).getContent(), "text1");
	EXPECT_EQ(conn->messages.at(3).getTime(), 12);
	EXPECT_EQ(conn->messages.at(3).getSender(), 1);
	EXPECT_EQ(conn->messages.at(3).getChat(), 1);

	ASSERT_TRUE(conn->messages.contains(4));
	EXPECT_EQ(conn->messages.at(4).getId(), 4);
	EXPECT_EQ(conn->messages.at(4).getContent(), "text2");
	EXPECT_EQ(conn->messages.at(4).getTime(), 50);
	EXPECT_EQ(conn->messages.at(4).getSender(), 2);
	EXPECT_EQ(conn->messages.at(4).getChat(), 1);
	
}

TEST(MessageRepoTests, getById){
	std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);

	std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
	
	conn->messages.insert(std::make_pair(1, Message(1, "test1", 12, 1, 1)));
	conn->messages.insert(std::make_pair(2, Message(2, "test2", 50, 2, 1)));

	EXPECT_CALL(*conn, reGet(::testing::_)).Times(2);
	MessageRepo repo((DBConnection<iConnection>*) connections.get());

	std::vector<int> ids = { 3 };

	std::vector<iMessage> messages = repo.getByID(ids);
	EXPECT_TRUE( messages.empty() );

	ids = { 1, 2 };
	messages = repo.getByID(ids);

	ASSERT_EQ(messages.size(), 2 );

	EXPECT_EQ(messages[0].getId(), 1);
	EXPECT_EQ(messages[0].getContent(), "test1");
	EXPECT_EQ(messages[0].getTime(), 12);
	EXPECT_EQ(messages[0].getSender(), 1);
	EXPECT_EQ(messages[0].getChat(), 1);
	
	EXPECT_EQ(messages[1].getId(), 2);
	EXPECT_EQ(messages[1].getContent(), "test2");
	EXPECT_EQ(messages[1].getTime(), 50);
	EXPECT_EQ(messages[1].getSender(), 2);
	EXPECT_EQ(messages[0].getChat(), 1);
}

//
//end of MessageRepo Section
//