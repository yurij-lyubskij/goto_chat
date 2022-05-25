#include <gtest/gtest.h>
#include "ChatRoomHandler.h"
#include "../DBRepo/tests/reDBConnection.h"
#include "Request.h"
#include "Response.h"

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

TEST(ChatRoomHandlersTests, CreateChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(testing::AtLeast(0));
    CreateChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.CanHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    testRequest.cookie = "1";
    testRequest.body = "{\"chatName\": \"someChat\" ,\"usersCount\": 2,\"users\": [1, 2]}";

    EXPECT_TRUE(handler.CanHandle(testRequest));
    Response result;

    result = handler.Handle(testRequest);
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "{\"chatId\":1}");
    EXPECT_EQ(result.statusCode, OK);

    result = handler.Handle(testRequest);
    EXPECT_EQ(result.statusCode, BadRequest);
}

TEST(ChatRoomHandlersTests, JoinChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    std::shared_ptr<MockConnection> conn = connections->connection();
	connections->freeConnection(conn);
    conn->chats.insert(std::make_pair(1, ChatRoom(1, "test")));

	EXPECT_CALL(*conn, reExec(::testing::_, ::testing::_)).Times(testing::AtLeast(0));
    JoinChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.CanHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/join";
    testRequest.cookie = "1";
    testRequest.body = "1 1";
    EXPECT_TRUE(handler.CanHandle(testRequest));
    
    Response result;
    result = handler.Handle(testRequest);   
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "");
    EXPECT_EQ(result.statusCode, 200);

    result = handler.Handle(testRequest);
    EXPECT_EQ(result.statusCode, 400);
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
    testRequest.target = "/chat/find";
    testRequest.cookie = "1";
    testRequest.body = "test";
    EXPECT_TRUE(handler.CanHandle(testRequest));
    Response result;
    result = handler.Handle(testRequest);   
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.body, "1 test\n3 testing\n");
    EXPECT_EQ(result.statusCode, 200);
      
}
