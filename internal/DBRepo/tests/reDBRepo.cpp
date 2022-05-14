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

	conn->chats.insert(std::make_pair(2, ChatRoom(2, "test")));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(2);
	ChatRepo repo((DBConnection<iConnection>*) connections.get());

	EXPECT_FALSE(repo.doesExist(1));
	EXPECT_TRUE(repo.doesExist(2));
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

	ASSERT_THAT(repo.put(chats),  testing::ElementsAre(1, 2));
	chats = repo.getByID(ids);
	
	ASSERT_EQ(chats.size(), 2);
	EXPECT_EQ(chats[0].getId(), chat1.getId());
	EXPECT_EQ(chats[1].getId(), chat2.getId());
}

/*
TEST(ChatRepoTests, adding){
	ChatRoom chat(1);
	User usr;
	usr.Id = 1;
	usr.Name = "abc";
	usr.PhoneNumber = "1234567890";
	chat.addUser(usr);
	std::vector<User> mems = chat.getMembers();
	EXPECT_EQ(mems.size(), 1);
	EXPECT_EQ(mems[0].Id, 1);
	EXPECT_EQ(mems[0].Name, "abc");
	EXPECT_EQ(mems[0].PhoneNumber, "1234567890");
}

TEST(ChatTests, removing){
	ChatRoom chat(1);
	User usr;
	usr.Id = 1;
	usr.Name = "abc";
	usr.PhoneNumber = "1234567890";
	chat.addUser(usr);
	chat.removeUser(usr);
	std::vector<User> mems = chat.getMembers();
	EXPECT_EQ(mems.size(), 0);
}
*/

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

	EXPECT_THAT(repo.put(messages),  testing::ElementsAre(1));
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

	EXPECT_THAT(repo.put(messages),  testing::ElementsAre(1, 2));
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