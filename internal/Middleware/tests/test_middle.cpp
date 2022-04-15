#include <gtest/gtest.h>

#include <MiddleWare.h>

TEST(Middleware, CheckAuth) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.URL = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    Response test_result;
    test_result.body = "TEST_RESULT";
    test_result.statusCode = 200;
    CheckAuth middle;
    bool can = middle.CanHandle(req);
    EXPECT_EQ(true, can);
    Request result = handler.Handle(req);
    EXPECT_EQ(test_result.body, result.body);
}