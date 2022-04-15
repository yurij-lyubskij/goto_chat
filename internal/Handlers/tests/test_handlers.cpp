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