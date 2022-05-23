#include <gtest/gtest.h>

#include <MiddleWare.h>
#include <jsonParser.h>

TEST(Middleware, CheckAuth) {
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    req.responseStatus = 200;
    Request test_result = req;
    test_result.body = "TEST_DATA";
    test_result.responseStatus = 401;
    std::shared_ptr<iAuthDb> auth(new AuthDb);
    CheckAuth middle(auth);
    jsonParser parser;
    User test = parser.parseUser(req.body);
    auth->SetCookie(test);
    Request result = middle(req);
    EXPECT_EQ(test_result.responseStatus, result.responseStatus);
    EXPECT_EQ(test_result.body, result.body);
}