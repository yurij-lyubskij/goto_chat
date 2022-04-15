#include <gtest/gtest.h>

#include "UserSession.h"

TEST(UserSession, Read) {
    UserSession session;
    std::string result = session.Read();
    std::string test_result = "some_data_read";
    EXPECT_EQ(result, test_result);
}


TEST(UserSession, Write) {
    UserSession session;
    std::string test_data = "some_data_to_write";
    EXPECT_NO_THROW(session.Write(test_data));
}
