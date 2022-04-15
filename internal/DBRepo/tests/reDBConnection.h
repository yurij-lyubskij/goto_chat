#ifndef SERVER_REDBCONNECTION
#define SERVER_REDBCONNECTION

#include "DBRepo.h"

class DullConnection{
    private:
        //no actual connection
    public:
        bool exec(enum Operation, std::vector<DBObject>);
        std::vector<DBObject> get(std::string);
};

#endif