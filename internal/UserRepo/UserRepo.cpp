//
// Created by yura11011 on 14.04.2022.
//

#include "UserRepo.h"



std::vector<User> UserRepo::GetManybyPhone(std::vector<std::string> phone){
    std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

    DBRequest request;
    request.operation = getWithPhone;
    request.objectType = user;
    request.request = "";
    for(auto i: phone) {
        request.request += i;
    }
    std::vector<DBObject> objects = conn->get(request);

    size_t len = objects.size();													//objects with some ids might don't exist so check size
    std::vector<User> users;
    for(size_t i = 0; i < len; ++i) {
        users.push_back(objects[i]);
    }

    connection->freeConnection(conn);										//return connection to the queue

    return users;
}

User UserRepo::GetbyPhone(std::string Phone) {
    std::vector<std::string> phone;
    phone.push_back(Phone);
    std::vector<User> users = GetManybyPhone(phone);
    if (users.empty()) {
        return User();
    }
    return users.front();
}

std::vector<User> UserRepo::getManyByID(std::vector<size_t> id) {
    std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB

    DBRequest request;
    request.operation = getFew;
    request.objectType = user;
    request.request = "";
    for(auto i: id) {
        request.request += i;
    }

    std::vector<DBObject> objects = conn->get(request);

    size_t len = objects.size();													//objects with some ids might don't exist so check size
    std::vector<User> users;
    for(size_t i = 0; i < len; ++i) {
        users.push_back(objects[i]);
    }

    connection->freeConnection(conn);										//return connection to the queue

    return users;
}


User UserRepo::GetbyId(size_t id) {
    std::vector<size_t> ids;
    ids.push_back(id);
    std::vector<User> users = getManyByID(ids);
    if (users.empty()) {
        return User();
    }
    return users.front();
}

bool UserRepo::CreateMany(std::vector<User> users) {
    std::shared_ptr<iConnection> conn = connection->connection();			//getting connection to DB
    int len = users.size();
    std::vector<DBObject> objects;
    for(int i = 0; i < len; ++i) {
        objects.push_back(DBObject(users[i]));
        if ( users[i].PhoneNumber == "" ) {
            connection->freeConnection(conn);								//return connection to the queue
            return false;
        }
    }
    DBRequest request;
    request.operation =  putIt;
    request.objectType = user;
    request.request = "";

    std::vector<DBObject> res = conn->exec( request , objects );
    connection->freeConnection(conn);										//return connection to the queue

    if( res.empty() ) return false;
    else return true;
}



bool UserRepo::CreateUser(User user) {
    std::vector<User> users;
    users.push_back(user);
    return CreateMany(users);
}



