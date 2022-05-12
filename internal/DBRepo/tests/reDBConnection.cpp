#include <gtest/gtest.h>
#include "reDBConnection.h"



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