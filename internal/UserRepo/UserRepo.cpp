//
// Created by yura11011 on 14.04.2022.
//

#include "UserRepo.h"


size_t UserRepo::CreateUser(User user) {
    user.Id = ++counter;
    UserMap[user.Id] = user;
    UserbyPhone[user.PhoneNumber] = user;
    return user.Id;
}

User UserRepo::GetbyId(size_t id) {
    return UserMap[id];
}

User UserRepo::GetbyPhone(std::string Phone){
    return UserbyPhone[Phone];
}

bool UserRepo::UpdateUser(User user) {
    UserMap.erase(user.Id);
    UserbyPhone.erase(user.PhoneNumber);
    UserMap[user.Id] = user;
    UserbyPhone[user.PhoneNumber] = user;
    return true;
}

std::vector<User> UserRepo::getManyByID(std::vector<size_t> id) {
    std::vector<User> result;
    result.reserve(id.size());
    for (auto i : id) {
        result.emplace_back(UserMap[i]);
    }
    return result;
}

bool UserRepo::update(std::vector<User> users) {
    for (const auto& user : users) {
        UserbyPhone.erase(user.PhoneNumber);
        UserMap.erase(user.Id);
        UserMap[user.Id] = user;
        UserbyPhone[user.PhoneNumber] = user;
    }
    return true;
}

bool UserRepo::CreateMany(std::vector<User> users) {
    for (const auto& user : users) {
        UserMap[user.Id] = user;
        UserbyPhone[user.PhoneNumber] = user;
    }
    return true;
}
