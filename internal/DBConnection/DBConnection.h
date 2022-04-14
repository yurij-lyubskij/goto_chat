#ifndef DB_CONNECTION
#define DB_CONNECTION

#include <stdlib.h>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <libpq-fe.h>
#include "DBRepo.h"

enum DBObjectType { user, chat, message, input };

typedef struct{
    DBObjectType objectType;
    std::string request;
} DBRequest;

enum Operation { putIt, deleteIt, updateIt };

class DBObject{
    public:
        DBObjectType type;
        std::vector<std::string> attr;
        DBObject();
        DBObject(*UserDB);
        DBObject(*ChatDB);
        DBObject(*MessageDB);
        //DBObject(InputDB);        
};

class iConnection{
    public:
        virtual bool exec(Operation, std::vector<DBObject>) = 0;
        virtual std::vector<DBObject> get(DBRequest);
        
};

class PGConnection : public iConnection{
    private:
        void establish_connection();
        std::shared_ptr<PGconn>  m_connection;
   public:
    PGConnection();
    std::shared_ptr<PGconn> connection() const;
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


#endif