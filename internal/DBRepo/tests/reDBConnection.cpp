#include <gtest/gtest.h>
#include <map>
#include <utility>
#include "reDBConnection.h"
#include "User.h"

//
//MockConnection section
//
std::vector<DBObject> MockConnection::exec(DBRequest request, const std::vector<DBObject>& objects){
    std::vector<DBObject> res;
    reExec(request, objects);
    std::vector<std::string> attrs = split(request.request);
    int len = objects.size();
    switch(request.operation){
        case putIt:
            switch(request.objectType){
                case user:
                    {
                    for( int i = 0; i < len; ++i ) {
                        std::vector<User> usrs(len);
                        auto obj = objects[i];
                        usrs[i] = obj;
                        ++usersCount;
                        users.insert(std::make_pair(usersCount, usrs[i]));
                        userByPhone.insert(std::make_pair(usrs[i].PhoneNumber, usrs[i]));
                        res.push_back(User(usersCount));   
                    }
                    }
                    break;
                case chat:
                    {
                    std::vector<ChatRoom> chts;
                    for( int i = 0; i < len; ++i ) {
                        auto obj = objects[i];
                        chts.push_back(obj);
                        ++chatsCount;
                        chats.insert(std::make_pair(chatsCount, ChatRoom(chatsCount, chts[i].getName())));
                        res.push_back(ChatRoom(chatsCount));                  
                    }
                    }  
                    break;
                case message:
                    {
                    std::vector<iMessage> mess;
                    for( int i = 0; i < len; ++i ) {
                        auto obj = objects[i];
                        mess.push_back(obj);
                        ++mesCount;
                        messages.insert(std::make_pair(mesCount, Message(mesCount, mess[i].getContent(), mess[i].getTime(), mess[i].getSender(), mess[i].getChat())));
                        res.push_back(Message(mesCount));                 
                    }
                    }
                    break;
            }
            break;
        case checkIt:
            switch(request.objectType){
                case user:
                    {
                    User usr;
                    for( int i = 0; i < len; ++i ) {
                        auto obj = objects[i];
                        usr = obj;
                        if ( ! users.contains(usr.Id)) return res;
                    }
                    }
                    break;
                case chat:
                    {
                    for( int i = 0; i < len; ++i ) {
                        auto obj = objects[i];
                        ChatRoom cht = obj.operator ChatRoom();
                        if ( ! chats.contains(cht.getId())) return res;
                    }
                    }  
                    break;
                case message:
                    {
                    iMessage mes;
                    for( int i = 0; i < len; ++i ) {
                        auto obj = objects[i];
                        mes = obj;
                        if ( ! messages.contains(mes.getId())) return res;
                    }
                    }
                    break;
            }
            break;
        case addMembers:
        {
            auto obj = objects[0];
            ChatRoom cht = ChatRoom(obj);
            if ( ! chats.contains(cht.getId()) ) { return res; }
            --len;
            /*
            for( int i = 0; i < len; ++i ) {
                if ( users_chats.contains(usrs[i].Id) ) { return res; }
            }*/
            for( int i = 0; i < len; ++i ) {
                obj = objects[i+1];
                users_chats.insert(std::make_pair(User(obj).Id, cht.getId()));
                res.push_back(ChatRoom());
            }
        }
        break;
    }
    if ( res.empty() ) res.push_back(DBObject());
    return res;
};

std::vector<DBObject> MockConnection::get(DBRequest request){
    reGet(request);
    std::vector<DBObject> result;
    std::vector<std::string> attrs = split(request.request);
    switch(request.operation){
        case getFew:
            {
            int len = attrs.size();
            std::vector<int> ids(len);

            for( int i = 1; i < len; ++i ) ids[i-1] = std::stoi(attrs[i]);
            --len;

            switch(request.objectType){
                case user:
                    for( int i = 0; i < len; ++i ) {
                        if( users.contains(ids[i])) result.push_back(users.at(ids[i]));
                    }
                    break;
                case chat:
                    for( int i = 0; i < len; ++i ) {
                        if( chats.contains(ids[i])) result.push_back(chats.at(ids[i]));
                    }
                    break;
                case message:
                    for( int i = 0; i < len; ++i ) {
                        if( messages.contains(ids[i]) ) result.push_back(messages.at(ids[i]));
                    }
                    break;
            }
            }
            break;
        case findWithName:
            {
            std::string name = attrs[0];
            for(std::map<int, ChatRoom>::iterator it = chats.begin(); it != chats.end(); ++it) {
                if( it->second.getName().find(name) != std::string::npos )
                result.push_back(it->second);
            }
            }
            break;
        case getLast:/*
            {
            int chtId = std::stoi(attrs[0]);
            int start = std::stoi(attrs[1]) - 1;
            int end = std::stoi(attrs[2]);
            std::vector<int> mess = chats_messages.at(chtId);
            for ( int i = start; i < end; ++i )
                result.push_back(messages.at(mess[i]));
            }*/
            break;
        case getWithPhone:
            result.push_back(userByPhone[request.request]);
        break;
    }

    return result;
};

//
//end of MockConnection section
//

//
//DBConnection section
//

template<>
std::shared_ptr<MockConnection> DBConnection<MockConnection>::connection(){
	
    std::unique_lock<std::mutex> lock( m_mutex );

    while ( m_pool.empty() ){
            m_condition.wait( lock );
    }

    std::shared_ptr<MockConnection> conn = m_pool.front();
    m_pool.pop();

    return  conn;
};	

template<>
void DBConnection<MockConnection>::freeConnection(std::shared_ptr<MockConnection> conn)
{
    std::unique_lock<std::mutex> lock( m_mutex );
    m_pool.push( conn );
    lock.unlock();
    m_condition.notify_one();
}

template <>
void DBConnection<MockConnection>::createPool()
{
    std::lock_guard<std::mutex> locker( m_mutex );

    for ( auto i = 0; i< POOL; ++i ){
         m_pool.emplace ( std::make_shared<MockConnection>() );
    }
}

template<>
DBConnection<MockConnection>::DBConnection(){
	createPool();
};

template<>
DBConnection<MockConnection>::DBConnection(int _pool): POOL(_pool){ 
	createPool();
};

//
//end of DBConnection section
//