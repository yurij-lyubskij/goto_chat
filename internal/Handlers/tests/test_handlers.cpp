#include <gtest/gtest.h>

#include "Handler.h"

TEST(handlers, GetChatHistory) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    GetChatHistory handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, CreateChatRoom) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    CreateChatRoom handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, FindChatRoom) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    FindChatRoom handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, JoiChatRoom) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    JoiChatRoom handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, CreateNewUser) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    CreateNewUser handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, Login) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    Login handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, Logout) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    Logout handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}

TEST(handlers, SendMessage) {
    Request req;
    req.body = "TEST_DATA";
    Response test_result;
    test_result.body = "TEST_RESULT";
    SendMessage handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}
