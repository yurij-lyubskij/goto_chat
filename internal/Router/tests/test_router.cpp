#include <gtest/gtest.h>

#include <Router.h>

TEST(Router, UseMiddle) {
    Router router;
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "/user/create";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    req.responseStatus = 200;
    Request test_result = req;
    Request result = router.UseMiddle(req);
    EXPECT_EQ(result.responseStatus, test_result.responseStatus);
    EXPECT_EQ(test_result.body, result.body);
}

/*
TEST(Router, CallHandler) {
    Router router;
    std::shared_ptr<iHandler> create(new CreateNewUser);
    router.AddHandler(create);
    Request req;
    req.body = "TEST_DATA";
    req.method = "POST";
    req.target = "/user/create";
    req.cookie = "SFDA^S(:IAJ09msmdc";
    Response test_result;
    test_result.body = "TEST_RESULT";
    test_result.statusCode = 200;
    Response result = router.Route(req);
    EXPECT_EQ(test_result.statusCode, result.statusCode);
}
*/