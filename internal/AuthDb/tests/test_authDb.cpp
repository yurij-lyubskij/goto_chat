#include <gtest/gtest.h>

#include <AuthDb.h>
#include <User.h>

TEST(db, default) {
    User user;
    user.Name = "yura";
    AuthDb TestDb = AuthDb();
    std::string cookie = TestDb.SetCookie(user);
    User check = TestDb.GetUser(cookie);
    EXPECT_EQ(user.Name, check.Name);
}