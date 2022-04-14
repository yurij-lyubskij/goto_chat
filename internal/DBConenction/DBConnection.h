#ifndef DB_CONNECTION
#define DB_CONNECTION

#include <stdlib.h>

#include "DBRepo.h"

typedef struct{
    enum DBOBjectType;
    std::string request;
} DBRequest;
enum Operation = { put, delete, update };

class DBObject{
    public:
        DBObject(UserDB);
        DBObject(ChatDB);
        DBObject(MessageDB);
        //DBObject(InputDB);
        enum DBObjectType type;
        std::vector<string> attr;
};

class DBConnection{
public:
    DBConnection();
    DBConnection(int _pool);
    std::shared_ptr<iConnection> connection();					
    void freeConnection(std::shared_ptr<iConnection>);
private:
    void createPool();
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<std::shared_ptr<iConnection>> m_pool;				//multiple connections to evade creating new connections

    const int POOL = 4;
};

class IConnection{
    public:
        virtual bool exec(enum Operation, std::vector<DBobject>) = 0;
        virtual std::vector<DBobject> get(DBRequest);
        
}

class PGConnection : iConnection{
    private:
        PGconn conn;
    public:
        bool exec(enum Operation, std::vector<DBobject>);
        std::vector<DBobject> get(DBRequest);
}

#endif