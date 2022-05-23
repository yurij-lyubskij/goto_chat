#include <libpq-fe.h>
#include <sstream>
#include <iomanip>
#include <iostream>

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
                    return checkUsers(objects);
                    break;
                case chat:
                    return checkChats(objects);
                    break;
                case message:
                    return checkMessages(objects);
                    break;
            }
            break;
        case addMembers:
            return addMembersToChat(objects);
        break;
        
    }
    if ( res.empty() ) res.push_back(DBObject());
    return res;
}
//
//check Methods
//
std::vector<DBObject> PGConnection::checkUsers(std::vector<DBObject> users){ 
    //suppose to be                  SELECT EXISTS( SELECT us_id FROM users WHERE us_id = 
    const std::string baseRequest = "SELECT EXISTS( SELECT " + userIdCol + " FROM " + usersTableName + " WHERE " + userIdCol + " = ";
    const std::string endRequest = " );\n";
    std::string request = "";

    //making request
    for(DBObject object: users)
        request += baseRequest + object.attr[0] + endRequest;

    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //checking results. If one doesn't exist return empty vector otherwise with one fictional object
    std::vector<DBObject> result;
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            if( ((std::string) PQgetvalue (res ,0, 0)) == "f"){
                PQclear(res);
                return result;
            };

            PQclear(res);
        }
    }
    result.push_back(DBObject());
    return result;
};

std::vector<DBObject> PGConnection::checkChats(std::vector<DBObject> chats){
    //suppose to be                  SELECT EXISTS( SELECT ch_id FROM chats WHERE ch_id = 
    const std::string baseRequest = "SELECT EXISTS( SELECT " + chatIdCol + " FROM " + chatsTableName + " WHERE " + chatIdCol + " = ";
    const std::string endRequest = " );\n";
    std::string request = "";

    //making request
    for(DBObject object: chats)
        request += baseRequest + object.attr[0] + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //checking results. If one doesn't exist return empty vector otherwise with one fictional object
    std::vector<DBObject> result;
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            if( ((std::string) PQgetvalue (res ,0, 0)) == "f"){
                PQclear(res);
                return result;
            };

            PQclear(res);
        }
    }
    result.push_back(DBObject());
    return result;
};

std::vector<DBObject> PGConnection::checkMessages(std::vector<DBObject> messages){
    //suppose to be                  SELECT EXISTS( SELECT ms_id FROM messages WHERE ms_id = 
    const std::string baseRequest = "SELECT EXISTS( SELECT " + messageIdCol + " FROM " + messagesTableName + " WHERE " + messageIdCol + " = ";
    const std::string endRequest = " );\n";
    std::string request = "";

    //making request
    for(DBObject object: messages)
        request += baseRequest + object.attr[0] + endRequest;
    std::cout << request;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //checking results. If one doesn't exist return empty vector otherwise with one fictional object
    std::vector<DBObject> result;
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            if( ((std::string) PQgetvalue (res ,0, 0)) == "f"){
                PQclear(res);
                return result;
            };

            PQclear(res);
        }
    }
    result.push_back(DBObject());
    return result;
};
//
//check of put Methods
//

//
//put Methods
//
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
    const std::string endRequest = ")  RETURNING " + messageIdCol + ", " + messageTimeCol + ", " + userIdCol + ", " + chatIdCol + ";\n";

    const std::string baseInputWithTextRequest = "INSERT INTO " + inputsTableName + "(" + inputTypeCol + ", " + messageIdCol + ", " + textInputIdCol + ") VALUES(";
    const std::string baseInputWithVoiceRequest = "INSERT INTO " + inputsTableName + "(" + inputTypeCol + ", " + messageIdCol + ", " + voiceInputIdCol + ") VALUES(";
    const std::string endInputRequest = ");\n";

    const std::string baseTextRequest = "INSERT INTO " + textInputsTableName + "(" + textInputContentCol + ") VALUES(";
    const std::string endTextRequest = ")  RETURNING " + textInputIdCol + ", " + textInputContentCol + ";\n";

    const std::string baseVoiceRequest = "INSERT INTO " + voiceInputsTableName + "(" + voiceInputContentCol + ") VALUES(";
    const std::string endVoiceRequest = ")  RETURNING " + voiceInputIdCol + ", " + voiceInputContentCol + ";\n";

    std::string request = "";
    std::vector<DBObject> ids;
    std::vector<std::string> inputIds;
    std::vector<std::string> inputs;

    //putting inputs themselves
    {
    for(DBObject object: messages){
        if(object.attr[5] == "0")
            request += baseTextRequest + "'" + object.attr[1] + "'" + endTextRequest;
        else
            request += baseVoiceRequest + "'" + object.attr[1] + "'" + endVoiceRequest;
    }
    //sending request for inputs themselves
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids for general inputs
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            inputIds.push_back( PQgetvalue (res ,0, 0) ) ;
            inputs.push_back( PQgetvalue (res ,0, 1) );

            PQclear(res);
        }
    }
    }
    
    //putting messeges
    {
    request = "";
    time_t sendTime;
    for(DBObject object: messages){
        sendTime = std::time(NULL);
        request += baseRequest + "'" + std::asctime( std::localtime(&sendTime)) + "' ," + "'" + object.attr[3] + "' ," + "'" + object.attr[4] + "'" + endRequest;
    }
    //sending request for inputs
    PQsendQuery( m_connection.get(), request.c_str() );
    //getting ids for general inputs and returning
    PGresult* res;
    DBObject obj;
    obj.type = message;
    obj.attr = std::vector<std::string>(6);
    int i = 0;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = inputs[i];
            std::time_t time = convertTimeStamp(PQgetvalue (res ,0, 1));
            obj.attr[2] = std::to_string(time);
            obj.attr[3] = PQgetvalue (res ,0, 2);
            obj.attr[4] = PQgetvalue (res ,0, 3);
            obj.attr[5] = messages[i].attr[5];
            
            ids.push_back( obj ) ;

            PQclear(res);
        }
        ++i;
    }
    }
    
    //putting general inputs
    {
    request = "";
    int len = ids.size();
    for(int i = 0; i < len; ++i){
        if(ids[i].attr[5] == "0")
            request += baseInputWithTextRequest + "'" + "0" + "', " + "'" + ids[i].attr[0]  + "', " + "'" + inputIds[i] + "'" + endInputRequest;
        else
            request += baseInputWithVoiceRequest + "'" + "1" + "', " + "'" + ids[i].attr[0]  + "', " + "'" + inputIds[i] + "'" + endInputRequest;
    }
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            PQclear(res);
        }
    }
    }
    return ids;
};
//
//end of put Methods
//

std::vector<DBObject> PGConnection::addMembersToChat(std::vector<DBObject> chatAndUsers){
    //suppose to be                 INSERT INTO users_chats(us_id, ch_id) VALUES(
    const std::string baseRequest = "INSERT INTO " + usersChatsTableName + "(" + userIdCol + ", " + chatIdCol + ") VALUES(";
    const std::string endRequest = ");\n";
    std::string request = "";
    std::vector<DBObject> result;

    //making request
    std::string chatId = chatAndUsers[0].attr[0];
    int len = chatAndUsers.size();
    if(len < 2) return result;
    for( int i = 1; i < len; ++i)
        request += baseRequest + "'" + chatAndUsers[i].attr[0] + "', '" + chatId + "'" + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            PQclear(res);
        }
    }

    result.push_back(DBObject());
    return result;
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

time_t PGConnection::convertTimeStamp(char* str){
	time_t result = -1;
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
	if (sscanf(str, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900;
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = hour;
        breakdown.tm_min = min;
        breakdown.tm_sec = sec;
        result = mktime(&breakdown);
    }
    return result;
}
//
//end of PGConnection Section
//