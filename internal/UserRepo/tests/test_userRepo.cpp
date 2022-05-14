#include <gtest/gtest.h>

#include "UserRepo.h"

TEST(UserRepo, CreateUser) {
    UserRepo repo;
    User user;
    user.Id = 1;
    size_t id = repo.CreateUser(user);
    EXPECT_NE(id, 0);
}

TEST(UserRepo, GetbyId) {
    UserRepo repo;
    User user;
    user.Name = "VANYA";
    size_t id = repo.CreateUser(user);;
    User result = repo.GetbyId(id);
    EXPECT_EQ(result.Name, user.Name);
}

TEST(UserRepo, CreateAndGet) {
    UserRepo repo;
    User user;
    user.Name = "VANYA";
    size_t id = repo.CreateUser(user);
    User result = repo.GetbyId(id);
    EXPECT_EQ(result.Name, user.Name);
}