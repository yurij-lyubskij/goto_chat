#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "User.h"
#include "reDBRepo.h"
#include "reDBConnection.h"

//
//UserRepo Section

/*
TEST(UserRepoTests, getById){
	MockConnection conn;
	EXPECT_CALL(conn, get(::testing::_)).Times(1);

	UserRepo repo;
	EXPECT_FALSE(repo.doesExist(1));

	User usr;
	usr.Id = 1;
	usr.Name = "abc";
	usr.PhoneNumber = "1234567890";
	std::vector<User> users;
	users.push_back(usr);

	repo.put(users);
	EXPECT_TRUE(repo.doesExist(1));
}
*/

//
//end of UserRepo Section
//