#include <gtest/gtest.h>

#include "Handler.h"

//TEST(handlers, GetChatHistory) {
//    Request req;
//    req.body = "TEST_DATA";
//    req.method = "GET";
//    req.URL = "server/chat/1/message?id=123";
//    Response test_result;
//    test_result.body = "TEST_RESULT";
//    test_result.statusCode = 200;
//    GetChatHistory handler;
//    bool can = handler.CanHandle(req);
//    EXPECT_EQ(true, can);
//    Response result = handler.Handle(req);
//    EXPECT_EQ(test_result.body, result.body);
//}
//
//TEST(handlers, CreateChatRoom) {
//    Request req;
//    req.body = "TEST_DATA";
//    req.method = "POST";
//    req.URL = "server/create/chat/?name=123";
//    Response test_result;
//    test_result.body = "TEST_RESULT";
//    test_result.statusCode = 200;
//    CreateChatRoom handler;
//    bool can = handler.CanHandle(req);
//    EXPECT_EQ(true, can);
//    Response result = handler.Handle(req);
//    EXPECT_EQ(test_result.body, result.body);
//}
//
//TEST(handlers, FindChatRoom) {
//    Request req;
//    req.body = "TEST_DATA";
//    req.method = "GET";
//    req.URL = "server/chat?name=123";
//    Response test_result;
//    test_result.body = "TEST_RESULT";
//    test_result.statusCode = 200;
//    FindChatRoom handler;
//    bool can = handler.CanHandle(req);
//    EXPECT_EQ(true, can);
//    Response result = handler.Handle(req);
//    EXPECT_EQ(test_result.body, result.body);
//}
//
//TEST(handlers, JoiChatRoom) {
//    Request req;
//    req.body = "TEST_DATA";
//    req.method = "POST";
//    req.URL = "server/join/chat?name=123";
//    Response test_result;
//    test_result.body = "TEST_RESULT";
//    test_result.statusCode = 200;
//    JoiChatRoom handler;
//    bool can = handler.CanHandle(req);
//    EXPECT_EQ(true, can);
//    Response result = handler.Handle(req);
//    EXPECT_EQ(test_result.body, result.body);
//}

//TEST(handlers, SendMessage) {
//    Request req;
//    req.body = "TEST_DATA";
//    req.method = "POST";
//    req.URL = "server/create/message";
//    Response test_result;
//    test_result.body = "TEST_RESULT";
//    test_result.statusCode = 200;
//    SendMessage handler;
//    bool can = handler.CanHandle(req);
//    EXPECT_EQ(true, can);
//    Response result = handler.Handle(req);
//    EXPECT_EQ(test_result.body, result.body);
//}

/*
TEST(handlers, CreateNewUser) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "/user/create";
    Response test_result;
    test_result.statusCode = 200;
    CreateNewUser handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.statusCode, result.statusCode);
}

TEST(handlers, Login) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "/session/create";
    Response test_result;
    test_result.statusCode = 200;
    std::shared_ptr<iAuthDb> auth(new AuthDb);
    std::shared_ptr<iUserRepo> repo(new UserRepo);
    Login handler(auth, repo);
    bool can = handler.CanHandle(req);
    jsonParser parser;
    User test = parser.parseUser(req.body);
    test.Id = repo->CreateUser(test);
    req.cookie = auth->SetCookie(test);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.statusCode, result.statusCode);
}

TEST(handlers, Logout) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "/session/delete";
    Response test_result;
    test_result.statusCode = 200;
    Logout handler;
    bool can = handler.CanHandle(req);
    EXPECT_EQ(true, can);
    Response result = handler.Handle(req);
    EXPECT_EQ(test_result.statusCode, result.statusCode);
}
*/