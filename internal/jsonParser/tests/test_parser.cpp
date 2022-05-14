#include <gtest/gtest.h>

#include "jsonParser.h"

TEST(Parser, serializeUser) {
    jsonParser Parser;
    User user;
    user.Id = 2;
    user.PhoneNumber = "9165566777";
    user.Name = "name";
    std::string test = R"({"Id":"2","Name":"name","PhoneNumber":"9165566777"})";
    std::string result = Parser.serializeUser(user);
    EXPECT_EQ(result, test);
}

