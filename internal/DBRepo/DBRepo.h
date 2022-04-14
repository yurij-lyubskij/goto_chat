#ifndef DATA_BASE_REPOS
#define DATA_BASE_REPOS



#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <libpq-fe.h>

#include "ChatRoom.h"
#include "User.h"
#include "Message.h"

typedef struct{
	int id;
	std::string phone;
	std::string name;
} UserDB;

typedef struct{
	int id;
	std::string name;
} ChatDB;

typedef struct{
	int id;
	int senderID;
	time_t time;
} MessageDB;

typedef struct{
	int id;
	FILE* content;
} InputDB;

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
        DBObject(&UserDB);
        DBObject(&ChatDB);
        DBObject(&MessageDB);
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

template <class Connection>
class DBConnection{
public:
    DBConnection();
    DBConnection(int _pool);
    std::shared_ptr<Connection> connection();					
    void freeConnection(std::shared_ptr<Connection>);
private:
    void createPool();
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<std::shared_ptr<Connection>> m_pool;				//multiple connections to evade creating new connections

    const int POOL = 4;
};

//Interface Block
class iUserRepo{
	private:
		DBConnection<PGConnection> *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual User* getByID(int id[], int len);
		virtual bool update(User users[], int len);
		virtual bool put(User usrs[], int len);
		virtual User* getChatMembers(ChatRoom chat);
		virtual User* getSender(Message mes);
};

class iChatRepo{
	private:
		DBConnection<PGConnection> *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual ChatRoom* getByID(int id[], int len);
		virtual bool update(ChatRoom chats[], int len);
		virtual bool put(ChatRoom chats[], int len);
		virtual bool addUserToChat(ChatRoom chat, User user);
		virtual ChatRoom getMesChat(Message mes);
		virtual ChatRoom* getUserChats(User user);
};

class iMessageRepo{
	private:
		DBConnection<PGConnection> *connection;
	public:
		virtual bool doesEsixt(int id);
		virtual Message* getByID(int id[], int len);
		virtual bool update(Message mes[], int len);
		virtual bool put(Message mes[], int len);
		virtual Message* getFromRange(int start, int end, ChatRoom chat);
};

//Declaration block
class UserRepo: public iUserRepo{
	public:
		UserRepo(*DBConnection);
		bool doesEsixt(int id);
		User* getByID(int id[], int len);
		bool update(User users[], int len);
		bool put(User usrs[], int len);
		User* getChatMembers(ChatRoom chat);
		User* getSender(Message mes);
};

class ChatRepo: public iChatRepo{
	public:
		bool doesEsixt(int id);
		ChatRoom* getByID(int id[], int len);
		bool update(ChatRoom chats[], int len);
		bool put(ChatRoom chats[], int len);
		bool addUserToChat(ChatRoom chat, User user);
		ChatRoom getMesChat(Message mes);
		ChatRoom* getUserChats(User user);
};

class MessageRepo: public iMessageRepo{
	public:
		bool doesEsixt(int id);
		Message* getByID(int id[], int len);
		bool update(Message mes[], int len);
		bool put(Message mes[], int len);
		Message* getFromRange(int start, int end, ChatRoom chat);
};

/*
class InputRepo: public DBRepo{
	private:
		DBConnection *connection;
	public:
		bool doesEsixt(int id);
		Input* getByID(int id[], int len);
		bool update(Inputs inputs[], int len);
		bool put(Inputs inputs[], int len);
		Inputs* getInputs(Message mes);
};
*/

#endif