#include <libpq-fe.h>
#include <sstream>
#include <iomanip>
#include <iterator>

#include "DBRepo.h"

#include <iostream>
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
    //suppose to be                  INSERT INTO users(us_name, us_phone, us_password) VALUES(;
    const std::string baseRequest = "INSERT INTO " + usersTableName + "(" + userNameCol + ", " + userPhoneCol + ", " + userPasswordeCol + ") VALUES(";
    const std::string endRequest = ")  RETURNING " + userIdCol + ", " + userNameCol + ", " + userPhoneCol + ", " + userPasswordeCol + ";\n";
    std::string request = "";
    std::vector<DBObject> ids;

    //making request
    for(DBObject object: users)
        request += baseRequest + "'" + object.attr[1] + "' ," + "'" + object.attr[2] + "' ," + "'" + object.attr[3] +"'" + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );
    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = user;
    obj.attr = std::vector<std::string>(4);
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            obj.attr[2] = PQgetvalue (res ,0, 2);
            obj.attr[3] = PQgetvalue (res ,0, 3);
            
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
    const std::string endRequest = ") ON CONFLICT DO NOTHING RETURNING " + userIdCol + ";\n";
    std::string request = "";
    std::vector<DBObject> result;

    //making request
    std::string chatId = chatAndUsers[0].attr[0];
    int len = chatAndUsers.size();
    if(len < 2) return result;
    for( int i = 1; i < len; ++i)
        request += baseRequest + "'" + chatAndUsers[i].attr[0] + "', '" + chatId + "'" + endRequest;
    std::cout << request << std::endl;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            result.push_back(DBObject());
            PQclear(res);
        }
    }

    return result;
};

std::vector<DBObject> PGConnection::get(DBRequest request){
    std::vector<DBObject> result;
    std::vector<std::string> attrs = split(request.request);
    switch(request.operation){
        case getFew:
            {
            std::vector<std::string> ids(attrs.begin() + 1, attrs.end());
            switch(request.objectType){
                case user:
                    return getUsersById(ids);
                    break;
                case chat:
                    return getChatsById(ids);
                    break;
                case message:
                    return getMessagesById(ids);
                    break;
            }
            }
            break;
        case findWithName:
            return getChatsByName(request.request);
            break;
        case getWithPhone:
            return getUsersByPhone(attrs);
            break;
        case getLast:
            return getLastMessages(attrs[0], attrs[1]);
            break;
        case getLastVoice:
            return getLastVoiceMessages(attrs[0], attrs[1]);
            break;
    }

    return result;
}

//
//Get by id section
//
std::vector<DBObject> PGConnection::getUsersById(std::vector<std::string> ids){
    //suppose to be                 SELECT * FROM users WHERE us_id=32;
    const std::string baseRequest = " SELECT * FROM " + usersTableName + " WHERE " + userIdCol + " = ";
    const std::string endRequest = " ORDER BY us_id;\n";
    std::string request = "";

    //making request
    for(std::string id: ids)
        request += baseRequest + id + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = user;
    obj.attr = std::vector<std::string>(4);
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            obj.attr[2] = PQgetvalue (res ,0, 2);
            obj.attr[3] = PQgetvalue (res ,0, 3);
            
            result.push_back( obj ) ;

            PQclear(res);
        }
    }
    return result;
};

std::vector<DBObject> PGConnection::getChatsById(std::vector<std::string> ids){
    //suppose to be                 SELECT * FROM users WHERE us_id = 
    const std::string baseRequest = " SELECT * FROM " + chatsTableName + " WHERE " + chatIdCol + " = ";
    const std::string endRequest = " ORDER BY ch_id;\n";
    std::string request = "";

    //making request
    for(std::string id: ids)
        request += baseRequest + id + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = chat;
    obj.attr = std::vector<std::string>(3);
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            
            result.push_back( obj ) ;

            PQclear(res);
        }
    }
    return result;
};

std::vector<DBObject> PGConnection::getMessagesById(std::vector<std::string> ids){
    //suppose to be                 SELECT ms_id, ms_sendTime, ip_type, tip_content, vip_content, us_id, ch_id FROM (SELECT * FROM messages WHERE ms_id = 28
    const std::string baseRequest = "SELECT " + messageIdCol + ", " + messageTimeCol + ", " + inputTypeCol + "," +
                                        textInputContentCol + ", " + voiceInputContentCol + ", " + userIdCol + ", " + chatIdCol +
                                        " FROM (SELECT * FROM " + messagesTableName + " WHERE " + messageIdCol + " = ";
    //suppose to be                 ) AS MESSAGE join inputs using(ms_id) left join textinputs using(tip_id) left join voiceinputs using(vip_id) join users using(us_id) join chats using(ch_id);
    const std::string endRequest = ") AS MESSAGE join " + inputsTableName + " using(" + messageIdCol + ") left join " + textInputsTableName + " using(" +
                                    textInputIdCol + ") left join " + voiceInputsTableName + " using(" + voiceInputIdCol + ");\n";
    std::string request = "";

    //making request
    for(std::string id: ids)
        request += baseRequest + id + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    //getting ids for general inputs and returning
    PGresult* res;
    DBObject obj;
    obj.type = message;
    obj.attr = std::vector<std::string>(6);
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = (PQgetvalue (res ,0, 2)[0] == '0')? PQgetvalue (res ,0, 3) : PQgetvalue (res ,0, 4);
            std::time_t time = convertTimeStamp(PQgetvalue (res ,0, 1));
            obj.attr[2] = std::to_string(time);
            obj.attr[3] = PQgetvalue (res ,0, 5);
            obj.attr[4] = PQgetvalue (res ,0, 6);
            obj.attr[5] = PQgetvalue (res ,0, 2);
            
            result.push_back( obj ) ;

            PQclear(res);
        }
    }
    return result;
};
//
//end of get by id section
//
std::vector<DBObject> PGConnection::getUsersByPhone(std::vector<std::string> phones){
    //suppose to be                 SELECT * FROM users WHERE us_phone = 
    const std::string baseRequest = " SELECT * FROM " + usersTableName + " WHERE " + userPhoneCol + " LIKE '";
    const std::string endRequest = "';\n";
    std::string request = "";

    //making request
    for(std::string phone: phones)
        request += baseRequest + phone + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = user;
    obj.attr = std::vector<std::string>(4);
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {

            obj.attr[0] = PQgetvalue (res ,0, 0);
            obj.attr[1] = PQgetvalue (res ,0, 1);
            obj.attr[2] = PQgetvalue (res ,0, 2);
            obj.attr[3] = PQgetvalue (res ,0, 3);
            
            result.push_back( obj ) ;

            PQclear(res);
        }
    }
    return result;
};

std::vector<DBObject> PGConnection::getChatsByName(std::string name){
    //suppose to be                 SELECT * FROM chats WHERE ch_name LIKE '%Chat%';
    const std::string baseRequest = " SELECT * FROM " + chatsTableName + " WHERE " + chatNameCol + " LIKE '%";
    const std::string endRequest = "%';\n";
    std::string request = "";

    //making request
    request += baseRequest + name + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    //getting ids
    PGresult* res;
    DBObject obj;
    obj.type = chat;
    obj.attr = std::vector<std::string>(3);
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            int len = PQntuples(res);
            for(int i = 0; i < len; ++i){
                obj.attr[0] = PQgetvalue (res ,i , 0);
                obj.attr[1] = PQgetvalue (res ,i , 1);
                result.push_back( obj ) ;
            }
           

            PQclear(res);
        }
    }
    return result;
};

std::vector<DBObject> PGConnection::getLastMessages(std::string mesId, std::string number){
    /*
    //suppose to be                 SELECT ms_id, ms_sendTime, ip_type, tip_content, vip_content, us_id, ch_id FROM (SELECT * FROM messages WHERE ch_id = 
    const std::string baseRequest = "SELECT " + messageIdCol + ", " + messageTimeCol + ", " + inputTypeCol + "," +
                                        textInputContentCol + ", " + voiceInputContentCol + ", " + userIdCol + ", " + chatIdCol +
                                        " FROM (SELECT * FROM " + messagesTableName + " WHERE " + chatIdCol + " = ";
    //suppose to be                 ) AS MESSAGE join inputs using(ms_id) left join textinputs using(tip_id) left join voiceinputs using(vip_id);
    const std::string endRequest = ") AS MESSAGE join " + inputsTableName + " using(" + messageIdCol + ") left join " + textInputsTableName + " using(" +
                                    textInputIdCol + ") left join " + voiceInputsTableName + " using(" + voiceInputIdCol + ") join " + usersTableName +
                                    " using(" + userIdCol + ") join " + chatsTableName + " using(" + chatIdCol + ") ORDER BY ms_id;\n";
    std::string request = "";
*/
    //suppose to be                SELECT ms_id, ms_sendTime, tip_content, us_phone FROM (SELECT * FROM messages WHERE ch_id = 
    const std::string baseRequest = "SELECT " + messageIdCol + ", " + messageTimeCol + ", " + textInputContentCol + ", " + userPhoneCol + ", " + chatIdCol +
                                    " FROM (SELECT * FROM " + messagesTableName + " WHERE " + chatIdCol + " = " +
                                    "(SELECT ch_id FROM messages WHERE ms_id = ";
    //suppose to be                 ) AS MESSAGE join inputs using(ms_id) join textinputs using(tip_id) join users using(us_id);
    const std::string endRequest = ")) AS MESSAGE join " + inputsTableName + " using(" + messageIdCol + ") join " + textInputsTableName + " using(" +
                                    textInputIdCol + ") join " + usersTableName + " using(" + userIdCol + ") ORDER BY ms_id;\n";
    std::string request = "";

    //making request
    request = baseRequest + mesId + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );

    DBObject obj;
    obj.type = message;
    obj.attr = std::vector<std::string>(6);
    int num = std::stoi(number);
    PGresult* res;
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            int len = PQntuples(res);
            int start = len;
            while (PQgetvalue(res , start - 1, 0) != mesId && start > 0) --start;

            for(int i = 0; i < num && i + start < len; ++i){
                obj.attr[0] = PQgetvalue (res , start + i, 0);
                obj.attr[1] = PQgetvalue (res , start + i, 2);
                std::time_t time = convertTimeStamp(PQgetvalue (res , start + i, 1));
                obj.attr[2] = std::to_string(time);
                obj.attr[3] = PQgetvalue (res , start + i, 3);
                obj.attr[4] = PQgetvalue (res , start + i, 4);
                obj.attr[5] = "0";
                
                result.push_back( obj ) ;
            }
            PQclear(res);
        }
    }
    return result;
};

std::vector<DBObject> PGConnection::getLastVoiceMessages(std::string mesId, std::string number){
    /*
    //suppose to be                 SELECT ms_id, ms_sendTime, ip_type, tip_content, vip_content, us_id, ch_id FROM (SELECT * FROM messages WHERE ch_id = 
    const std::string baseRequest = "SELECT " + messageIdCol + ", " + messageTimeCol + ", " + inputTypeCol + "," +
                                        textInputContentCol + ", " + voiceInputContentCol + ", " + userIdCol + ", " + chatIdCol +
                                        " FROM (SELECT * FROM " + messagesTableName + " WHERE " + chatIdCol + " = ";
    //suppose to be                 ) AS MESSAGE join inputs using(ms_id) left join textinputs using(tip_id) left join voiceinputs using(vip_id);
    const std::string endRequest = ") AS MESSAGE join " + inputsTableName + " using(" + messageIdCol + ") left join " + textInputsTableName + " using(" +
                                    textInputIdCol + ") left join " + voiceInputsTableName + " using(" + voiceInputIdCol + ") join " + usersTableName +
                                    " using(" + userIdCol + ") join " + chatsTableName + " using(" + chatIdCol + ") ORDER BY ms_id;\n";
    std::string request = "";
*/
    //suppose to be                SELECT ms_id, ms_sendTime, tip_content, us_phone FROM (SELECT * FROM messages WHERE ch_id = 
    const std::string baseRequest = "SELECT " + messageIdCol + ", " + messageTimeCol + ", " + voiceInputContentCol + ", " + userPhoneCol + ", " + chatIdCol +
                                    " FROM (SELECT * FROM " + messagesTableName + " WHERE " + chatIdCol + " = " +
                                    "(SELECT ch_id FROM messages WHERE ms_id = ";
    //suppose to be                 ) AS MESSAGE join inputs using(ms_id) join textinputs using(tip_id) join users using(us_id);
    const std::string endRequest = ")) AS MESSAGE join " + inputsTableName + " using(" + messageIdCol + ") join " + voiceInputsTableName + " using(" +
                                    voiceInputIdCol + ") join " + usersTableName + " using(" + userIdCol + ") ORDER BY ms_id;\n";
    std::string request = "";
    
    //making request
    request = baseRequest + mesId + endRequest;
    //sending request
    PQsendQuery( m_connection.get(), request.c_str() );
    std::cout << request;
    DBObject obj;
    obj.type = message;
    obj.attr = std::vector<std::string>(6);
    int num = std::stoi(number);
    PGresult* res;
    std::vector<DBObject> result;
    while ( res = PQgetResult( m_connection.get()) ) {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res)) {
            int len = PQntuples(res);
            int start = len;
            while (PQgetvalue(res , start - 1, 0) != mesId && start > 0) --start;

            for(int i = 0; i < num && i + start < len; ++i){
                obj.attr[0] = PQgetvalue (res , start + i, 0);
                obj.attr[1] = PQgetvalue (res , start + i, 2);
                std::time_t time = convertTimeStamp(PQgetvalue (res , start + i, 1));
                obj.attr[2] = std::to_string(time);
                obj.attr[3] = PQgetvalue (res , start + i, 3);
                obj.attr[4] = PQgetvalue (res , start + i, 4);
                obj.attr[5] = "1";
                
                result.push_back( obj ) ;
            }
            PQclear(res);
        }
    }
    return result;
};

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