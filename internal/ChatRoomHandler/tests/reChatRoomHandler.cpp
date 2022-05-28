#include <gtest/gtest.h>
#include "ChatRoomHandler.h"
#include "../DBRepo/tests/reDBConnection.h"
#include "Request.h"
#include "Response.h"
/*
TEST(ChatRoomHandlersTests, GetMessage) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
    conn->chats.insert(std::make_pair(1, ChatRoom(1, "test")));
    conn->messages.insert(std::make_pair(1, Message(1, "test", 2, 3, 3)));
    conn->messages.insert(std::make_pair(2, Message(2, "test", 3, 2, 3)));
    conn->chats_messages.insert(std::make_pair(1, std::vector<int>({1 , 2})));

	EXPECT_CALL(*conn, reGet(::testing::_)).Times(testing::AtLeast(0));
    GetMessageFromChat handler((DBConnection<iConnection>*) connections.get());
    Request testRequest;
    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    EXPECT_FALSE(handler.CanHandle(testRequest));

    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    testRequest.cookie = "1";
    testRequest.body = "1 range 1 2";
    EXPECT_TRUE(handler.CanHandle(testRequest));

    Response result;

    EXPECT_TRUE(handler.CanHandle(testRequest));

    result = handler.Handle(testRequest);
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "test 2 3 3\ntest 3 2 3\n");
    EXPECT_EQ(result.statusCode, 200);

}
*/
TEST(ChatRoomHandlersTests, CreateChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);

    User usr1, usr2;
    usr1.Id = 1;
    usr1.Name = "TestName";
    usr1.PhoneNumber = "12345";
    usr1.password = "password";
    usr2.Id = 2;
    usr2.Name = "TestName";
    usr2.PhoneNumber = "12346";
    usr2.password = "password";
    conn->users.insert(std::make_pair(1, usr1));
    conn->users.insert(std::make_pair(1, usr2));
    conn->userByPhone.insert(std::make_pair("12345", usr1));
    conn->userByPhone.insert(std::make_pair("12346", usr1));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*conn, reGet(::testing::_)).Times(testing::AtLeast(0));
    CreateChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.CanHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    testRequest.cookie = "1";
    testRequest.body = "{\"chatName\": \"someChat\" ,\"usersCount\": 2,\"users\": [\"12345\",\"12346\"]}";

    EXPECT_TRUE(handler.CanHandle(testRequest));
    Response result;

    result = handler.Handle(testRequest);
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "{\"chatId\":1}");
    EXPECT_EQ(result.statusCode, OK);

}

TEST(ChatRoomHandlersTests, JoinChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
    User usr1, usr2;
    usr1.Id = 1;
    usr1.Name = "TestName";
    usr1.PhoneNumber = "12345";
    usr1.password = "password";
    usr2.Id = 2;

    conn->users.insert(std::make_pair(1, usr1));
    conn->userByPhone.insert(std::make_pair("12345", usr1));

    conn->chats.insert(std::make_pair(1, ChatRoom(1, "test")));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(testing::AtLeast(0));
    EXPECT_CALL(*conn, reGet(::testing::_)).Times(testing::AtLeast(0));
    JoinChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.CanHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/join";
    testRequest.cookie = "1";
    testRequest.body = "{\"chatId\": \"1\" ,\"user\": \"12345\"}";
    EXPECT_TRUE(handler.CanHandle(testRequest));
    
    Response result;
    result = handler.Handle(testRequest);   
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "");
    EXPECT_EQ(result.statusCode, 200);

}

TEST(ChatRoomHandlersTests, FindChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
    conn->chats.insert(std::make_pair(1, ChatRoom(1, "test")));
    conn->chats.insert(std::make_pair(2, ChatRoom(2, "est")));
    conn->chats.insert(std::make_pair(3, ChatRoom(3, "testing")));

	EXPECT_CALL(*conn, reGet(::testing::_)).Times(testing::AtLeast(0));
    FindChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.CanHandle(testRequest));


    testRequest.method = "GET";
    testRequest.target = "/chat/find/?name=test";
    testRequest.cookie = "1";
    EXPECT_TRUE(handler.CanHandle(testRequest));
    Response result;
    result = handler.Handle(testRequest);   
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "{\"chatCount\":\"2\",\"chats\":[{\"id\":\"1\",\"chatName\":\"test\"},{\"id\":\"3\",\"chatName\":\"testing\"}]}");
    EXPECT_EQ(result.statusCode, 200);
      
}
