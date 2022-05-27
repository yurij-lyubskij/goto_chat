#include <gtest/gtest.h>
#include "ChatRoomHandler.h"
#include "Request.h"
#include "Response.h"

//TEST(ChatRoomHandlersTests, GetMessage) {
//
//    Request testRequest;
//    testRequest.body = "testRequestBody";
//    Response testResult;
//    testResult.body = "testResultBody";
//
//    GetMessageFromChat handler;
//    EXPECT_EQ(handler.CanHandle(testRequest), true);
//    EXPECT_EQ(handler.Handle(testRequest).body, testResult.body);
//}
//
//TEST(ChatRoomHandlersTests, CreateChatRoom) {
//
//    Request testRequest;
//    testRequest.body = "testRequestBody";
//    Response testResult;
//    testResult.body = "testResultBody";
//
//    CreateChatRoom handler;
//    EXPECT_EQ(handler.CanHandle(testRequest), true);
//    EXPECT_EQ(handler.Handle(testRequest).body, testResult.body);
//}
//
//TEST(ChatRoomHandlersTests, JoinChatRoom) {
//
//    Request testRequest;
//    testRequest.body = "testRequestBody";
//    Response testResult;
//    testResult.body = "testResultBody";
//
//    JoinChatRoom handler;
//    EXPECT_EQ(handler.CanHandle(testRequest), true);
//    EXPECT_EQ(handler.Handle(testRequest).body, testResult.body);
//}
//
//TEST(ChatRoomHandlersTests, FindChatRoom) {
//
//    Request testRequest;
//    testRequest.body = "testRequestBody";
//    Response testResult;
//    testResult.body = "testResultBody";
//
//    FindChatRoom handler;
//    EXPECT_EQ(handler.CanHandle(testRequest), true);
//    EXPECT_EQ(handler.Handle(testRequest).body, testResult.body);
//}
//
//TEST(ChatRoomHandlersTests, NotifyUsers) {
//
//    Request testRequest;
//    testRequest.body = "testRequestBody";
//    Response testResult;
//    testResult.body = "testResultBody";
//
//    NotifyUsers handler;
//    EXPECT_EQ(handler.CanHandle(testRequest), true);
//    EXPECT_EQ(handler.Handle(testRequest).body, testResult.body);
//}
