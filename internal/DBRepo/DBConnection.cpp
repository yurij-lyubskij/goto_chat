#include <queue>
#include <mutex>
#include <condition_variable>

#include <libpq-fe.h>

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

//
//PGConnection Section
//

PGConnection::PGConnection(){
    m_connection.reset( 
        PQsetdbLogin(   m_dbhost.c_str(), 
                        std::to_string(m_dbport).c_str(), 
                        nullptr, 
                        nullptr, 
                        m_dbname.c_str(), 
                        m_dbuser.c_str(), 
                        m_dbpass.c_str()), 
                    &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 ){
       throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
    }
}

std::vector<DBObject> PGConnection::putUsers(std::vector<DBObject> users){
    //suppose to be                  INSERT INTO users(us_name, us_phone) VALUES(;
    const std::string baseRequest = "INSERT INTO " + usersTableName + "(" + userNameCol + ", " + userPhoneCol + ") VALUES(";
    const std::string endRequest = ")  RETURNING " + userIdCol + ";\n";
    std::string request = "";
    std::vector<DBObject> ids;
    //making request
    for(DBObject object: users)
        request += baseRequest + "'" + object.attr[1] + "' ," + "'" + object.attr[2] +"'" + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );
    //getting ids
    PGresult* res;
    while ( res = PQgetResult( conn->connection().get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res_)) {
            ids.push_back( std::stoi( PQgetvalue (res ,0, 0) ) );
            PQclear( res );
        }
    }
};
//
//end of PGConnection Section
//
