#include <gtest/gtest.h>
#include <map>
#include <utility>
#include "reDBConnection.h"

//
//MockConnection section
//
std::vector<DBObject> MockConnection::exec(DBRequest request, std::vector<DBObject> objects){
    std::vector<DBObject> res;
    reExec(request, objects);
    std::vector<std::string> attrs = split(request.request);
    int len = objects.size();
    switch(request.operation){
        case putIt:
            switch(request.objectType){
                case user:
                    {
                    std::vector<User> usrs(len);
                    for( int i = 0; i < len; ++i ) {
                        usrs[i] = objects[i];
                        ++usersCount;
                        users.insert(std::make_pair(usersCount, usrs[i]));
                        res.push_back(User(usersCount));   
                    }
                    }
                    break;
                case chat:
                    {
                    std::vector<ChatRoom> chts;
                    for( int i = 0; i < len; ++i ) {
                        chts.push_back(objects[i]);
                        ++chatsCount;
                        chats.insert(std::make_pair(chatsCount, chts[i]));
                        res.push_back(ChatRoom(chatsCount));                  
                    }
                    }  
                    break;
                case message:
                    {
                    std::vector<iMessage> mess;
                    for( int i = 0; i < len; ++i ) {
                        mess.push_back(objects[i]);
                        ++mesCount;
                        messages.insert(std::make_pair(mesCount, mess[i]));
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
                        usr = objects[i];
                        if ( ! users.contains(usr.Id)) return res;
                    }
                    }
                    break;
                case chat:
                    {
                    for( int i = 0; i < len; ++i ) {
                        ChatRoom cht = objects[i].operator ChatRoom();
                        if ( ! chats.contains(cht.getId())) return res;
                    }
                    }  
                    break;
                case message:
                    {
                    iMessage mes;
                    for( int i = 0; i < len; ++i ) {
                        mes = objects[i];
                        if ( ! messages.contains(mes.getId())) return res;
                    }
                    }
                    break;
            }
            break;
        case addMembers:
        {   
            ChatRoom cht = objects[0].operator ChatRoom();
            std::vector<User> usrs;
            --len;
            std::cout << len << std::endl;
            for( int i = 0; i < len; ++i ) {
                std::cout << "P" << std::endl;
                usrs.push_back(User(objects[i+1]));
                std::cout << "P" << std::endl;
                if ( users_chats.contains(usrs[i].Id) ) { return res; }
                
            }
            for( int i = 0; i < len; ++i ) {
                users_chats.insert(std::make_pair(User(objects[i]).Id, cht.getId()));
                res.push_back(ChatRoom(chatsCount));
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