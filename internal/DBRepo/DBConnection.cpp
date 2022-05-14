#include <queue>
#include <mutex>
#include <condition_variable>

#include "DBRepo.h"


//
//DBConnection Section
//
template<>
std::shared_ptr<iConnection> DBConnection<iConnection>::connection(){
	
    std::unique_lock<std::mutex> lock( m_mutex );

    while ( m_pool.empty() ){
            m_condition.wait( lock );
    }

    std::shared_ptr<iConnection> conn = m_pool.front();
    m_pool.pop();

    return  conn;
};	

template<>
void DBConnection<iConnection>::freeConnection(std::shared_ptr<iConnection> conn)
{
    std::unique_lock<std::mutex> lock( m_mutex );
    m_pool.push( conn );
    lock.unlock();
    m_condition.notify_one();
}

template<class Connection>
DBConnection<Connection>::DBConnection(){
	createPool();
};

template<class Connection>
DBConnection<Connection>::DBConnection(int _pool): POOL(_pool){ 
	createPool();
};

template <class Connection>
void DBConnection<Connection>::createPool()
{
    std::lock_guard<std::mutex> locker( m_mutex );

    for ( auto i = 0; i< POOL; ++i ){
         m_pool.emplace ( std::make_shared<Connection>() );
    }
}

//
//end of DBConnection Section
//