#include <libpq-fe.h>

#include "DBRepo.h"


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

std::vector<DBObject> PGConnection::exec(DBRequest request, std::vector<DBObject> objects){
    std::vector<DBObject> res;
    std::vector<std::string> attrs = split(request.request);
    int len = objects.size();
    switch(request.operation){
        case putIt:
            switch(request.objectType){
                case user:
                    res = putUsers(objects);
                    break;
                case chat:
                    res = putChats(objects);
                    break;
                case message:
                    res = putMessages(objects);
                    break;
            }
            break;
        case checkIt:
            switch(request.objectType){
                case user:
                    break;
                case chat:
                    break;
                case message:
                    break;
            }
            break;
        case addMembers:
        break;
        
    }
    if ( res.empty() ) res.push_back(DBObject());
    return res;
}

std::vector<DBObject> PGConnection::putUsers(std::vector<DBObject> users){
    //suppose to be                  INSERT INTO users(us_name, us_phone) VALUES(;
    const std::string baseRequest = "INSERT INTO " + usersTableName + "(" + userNameCol + ", " + userPhoneCol + ") VALUES(";
    const std::string endRequest = ")  RETURNING " + userIdCol + ", " + userNameCol + ", " + userPhoneCol + ";\n";
    std::string request = "";
    std::vector<DBObject> ids;

    //making request
    for(DBObject object: users)
        request += baseRequest + "'" + object.attr[1] + "' ," + "'" + object.attr[2] +"'" + endRequest;

    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = user;
    obj.attr = std::vector<std::string>(3);
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            obj.attr[2] = PQgetvalue (res ,0, 2);
            
            ids.push_back( obj ) ;

            PQclear(res);
        }
    }
    return ids;
};

std::vector<DBObject> PGConnection::putChats(std::vector<DBObject> chats){
    //suppose to be                 INSERT INTO chats(ch_name) VALUES(
    const std::string baseRequest = "INSERT INTO " + chatsTableName + "(" + chatNameCol + ") VALUES(";
    const std::string endRequest = ")  RETURNING " + chatIdCol + ", " + chatNameCol + ";\n";
    std::string request = "";
    std::vector<DBObject> ids;

    //making request
    for(DBObject object: chats)
        request += baseRequest + "'" + object.attr[1] + "'" + endRequest;

    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = chat;
    obj.attr = std::vector<std::string>(2);
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            
            ids.push_back( obj ) ;

            PQclear(res);
        }
    }
    return ids;
};

std::vector<DBObject> PGConnection::putMessages(std::vector<DBObject> messages){
    //suppose to be                 INSERT INTO messages(ms_sendTime, us_id, ch_id) VALUES(
    const std::string baseRequest = "INSERT INTO " + messagesTableName + "(" + messageTimeCol + ", " + userIdCol + ", " + chatIdCol + ") VALUES(";
    const std::string endRequest = ")  RETURNING " + messageIdCol + ", " + messageTimeCol + ";\n";
    std::string request = "";
    std::vector<DBObject> ids;

    //making request
    for(DBObject object: messages)
        request += baseRequest + "'" + object.attr[2] + "' ," + "'" + object.attr[3] + "' ," + "'" + object.attr[4] + "'" + endRequest;

    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = message;
    obj.attr = std::vector<std::string>(2);
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            obj.attr[2] = PQgetvalue (res ,0, 2);
            obj.attr[3] = PQgetvalue (res ,0, 3);
            obj.attr[4] = PQgetvalue (res ,0, 4);
            
            ids.push_back( obj ) ;

            PQclear(res);
        }
    }
    return ids;
};

std::vector<DBObject> PGConnection::get(DBRequest request){
    std::vector<DBObject> result;
    std::vector<std::string> attrs = split(request.request);
    switch(request.operation){
        case getFew:
            break;
        case findWithName:
            break;
        case getRange:
            break;
    }

    return result;
}
//
//end of PGConnection Section
//