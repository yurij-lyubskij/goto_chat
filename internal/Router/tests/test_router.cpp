#include <gtest/gtest.h>

#include <Router.h>

TEST(Router, UseMiddle) {
    Router router;
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.URL = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    req.response.statusCode = 200;
    Request test_result = req;
    test_result.response.body = "TEST_RESULT";
    test_result.response.statusCode = 401;
    Request result = router.UseMiddle(req);
    EXPECT_EQ(result.response.statusCode, test_result.response.statusCode);
    EXPECT_EQ(test_result.response.body, result.response.body);
}

TEST(Router, SelectHandler) {
    Router router;
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.URL = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    bool result = router.SelectHandler(req);
    EXPECT_EQ(true, result);
}

TEST(Router, CallHandler) {
    Router router;
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.URL = "server/create/user?name=123";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    Response test_result;
    test_result.body = "TEST_RESULT";
    test_result.statusCode = 200;
    Response result = router.CallHandler(req);
    EXPECT_EQ(test_result.statusCode, result.statusCode);
    EXPECT_EQ(test_result.body, result.body);
}
