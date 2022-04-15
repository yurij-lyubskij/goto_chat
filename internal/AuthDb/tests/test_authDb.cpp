#include <gtest/gtest.h>

#include <AuthDb.h>

TEST(db, default) {
    std::string key = "123";
    AuthDb TestDb = AuthDb();
    std::string val1 = TestDb.SetCookie(key);
    std::string val2 = TestDb.GetCookie(key);
    EXPECT_EQ(val1, val2);
}