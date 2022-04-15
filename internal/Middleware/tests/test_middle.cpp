#include <gtest/gtest.h>

#include <MiddleWare.h>

TEST(Middleware, CheckAuth) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.URL = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    req.response.statusCode = 200;
    Request test_result = req;
    test_result.response.body = "TEST_RESULT";
    test_result.response.statusCode = 401;
    CheckAuth middle;
    Request result = middle(req, {});
    EXPECT_EQ(test_result.response.statusCode, result.response.statusCode);
    EXPECT_EQ(test_result.response.body, result.response.body);
}