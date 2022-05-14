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
    conn->messages.insert(std::make_pair(1, Message(1, "test", 2, 3)));
    conn->messages.insert(std::make_pair(2, Message(2, "test", 3, 2)));
    conn->chats_messages.insert(std::make_pair(1, std::vector<int>({1 , 2})));

	EXPECT_CALL(*conn, reGet(::testing::_)).Times(testing::AtLeast(0));
    GetMessageFromChat handler((DBConnection<iConnection>*) connections.get());
    Request testRequest;
    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    testRequest.cookie = "1";
    testRequest.body = "1 range 1 2";
    EXPECT_TRUE(handler.canHandle(testRequest));

    Response result;

    EXPECT_TRUE(handler.canHandle(testRequest));

    result = handler.handle(testRequest);
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.method, "GET");
    EXPECT_EQ(result.body, "test 2 3\ntest 3 2\n");
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
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    testRequest.cookie = "1";
    testRequest.body = "testName 1 1";

    EXPECT_TRUE(handler.canHandle(testRequest));
    Response result;

    result = handler.handle(testRequest);
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.method, "POST");
    EXPECT_EQ(result.body, "");
    EXPECT_EQ(result.statusCode, 200);

    result = handler.handle(testRequest);
    EXPECT_EQ(result.statusCode, 400);
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
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/join";
    testRequest.cookie = "1";
    testRequest.body = "1 1";
    EXPECT_TRUE(handler.canHandle(testRequest));
    
    Response result;
    result = handler.handle(testRequest);   
    EXPECT_EQ(result.cookie, "1");
    EXPECT_EQ(result.method, "POST");
    EXPECT_EQ(result.body, "");
    EXPECT_EQ(result.statusCode, 200);

    result = handler.handle(testRequest);
    EXPECT_EQ(result.statusCode, 400);
}

TEST(ChatRoomHandlersTests, FindChatRoom) {
    std::shared_ptr<DBConnection<MockConnection>> connections = std::make_shared<DBConnection<MockConnection>>(1);
    FindChatRoom handler((DBConnection<iConnection>*) connections.get());

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));


    testRequest.method = "GET";
    testRequest.target = "/chat/find";
    EXPECT_TRUE(handler.canHandle(testRequest));

    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";
      
    //EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}

/*
TEST(ChatRoomHandlersTests, NotifyUsers) {

    Request testRequest;
    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";

    NotifyUsers handler;
    EXPECT_EQ(handler.canHandle(testRequest), true);
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}
*/