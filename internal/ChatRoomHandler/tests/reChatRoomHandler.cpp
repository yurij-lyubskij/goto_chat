#include <gtest/gtest.h>
#include "ChatRoomHandler.h"
#include "Request.h"
#include "Response.h"

TEST(ChatRoomHandlersTests, GetMessage) {

    Request testRequest;
    testRequest.method = "GET";
    testRequest.URL = "/chat/message/list";
    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";

    GetMessageFromChat handler;
    EXPECT_EQ(handler.canHandle(testRequest), true);
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}

TEST(ChatRoomHandlersTests, CreateChatRoom) {
    CreateChatRoom handler;

    Request testRequest;
    testRequest.method = "GET";
    testRequest.URL = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.URL = "/chat/create";
    EXPECT_TRUE(handler.canHandle(testRequest));

    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";
      
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}

TEST(ChatRoomHandlersTests, JoinChatRoom) {
    JoinChatRoom handler; 

    Request testRequest;
    testRequest.method = "GET";
    testRequest.URL = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.URL = "/chat/join";
    EXPECT_TRUE(handler.canHandle(testRequest));

    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";
      
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}

TEST(ChatRoomHandlersTests, FindChatRoom) {
    FindChatRoom handler;

    Request testRequest;
    testRequest.method = "GET";
    testRequest.URL = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));


    testRequest.method = "GET";
    testRequest.URL = "/chat/find";
    EXPECT_TRUE(handler.canHandle(testRequest));

    testRequest.body = "testRequestBody";
    Response testResult;
    testResult.body = "testResultBody";
      
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
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