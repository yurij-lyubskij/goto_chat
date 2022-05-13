#include <gtest/gtest.h>
#include "ChatRoomHandler.h"
#include "Request.h"
#include "Response.h"

TEST(ChatRoomHandlersTests, GetMessage) {
    GetMessageFromChat handler;
    Request testRequest;
    testRequest.method = "POST";
    testRequest.target = "/chat/create";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    testRequest.body = "testRequestBody";
    EXPECT_TRUE(handler.canHandle(testRequest));

    Response testResult;
    testResult.body = "testResultBody";


    EXPECT_EQ(handler.canHandle(testRequest), true);
    EXPECT_EQ(handler.handle(testRequest).body, testResult.body);
}

TEST(ChatRoomHandlersTests, CreateChatRoom) {
    CreateChatRoom handler;

    Request testRequest;
    testRequest.method = "GET";
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/create";
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
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));

    testRequest.method = "POST";
    testRequest.target = "/chat/join";
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
    testRequest.target = "/chat/message/list";
    EXPECT_FALSE(handler.canHandle(testRequest));


    testRequest.method = "GET";
    testRequest.target = "/chat/find";
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