#include "reDBConnection.h"

TEST(ConnectionTest, putUsers) {
    PGConnection conn;
	User user1(0), user2(0);
	std::vector<DBObject> users;
	user1.Name = "abc";
	user1.PhoneNumber = "1234567890";

	user2.Name = "abcd";
	user2.PhoneNumber = "1234567890";

	users.push_back(user1);
	users.push_back(user2);

	DBRequest request;
	request.operation = putIt;
	request.objectType = user;
	request.request = "";

	users = conn.exec(request, users);
	ASSERT_EQ(users.size(), 2);
	EXPECT_EQ(users[0].attr[1], "abc");
	EXPECT_EQ(users[0].attr[2], "1234567890");
	EXPECT_EQ(users[1].attr[1], "abcd");
	EXPECT_EQ(users[1].attr[2], "1234567890");
}
