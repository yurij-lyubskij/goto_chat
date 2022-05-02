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
//#include <libpq-fe.h>

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
	std::string content;
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
		DBObject(const DBObject&);
		~DBObject();
        DBObject(const UserDB&);
        DBObject(const ChatDB&);
        DBObject(const MessageDB&);
		DBObject& operator=(const DBObject&);
        //DBObject(InputDB);        
};

class iConnection{
    public:
        virtual bool exec(Operation, std::vector<DBObject>) = 0;
        virtual std::vector<DBObject> get(DBRequest) = 0;
        
};

/*
//PostgreSQL connection
class PGConnection : public iConnection{
    private:
        void establish_connection();
        std::shared_ptr<PGconn>  m_connection;
   	public:
    	PGConnection();
    	std::shared_ptr<PGconn> connection() const;
};
*/

template <class Connection>
class DBConnection{
public:
    DBConnection(){};
    DBConnection(int _pool){};
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
	protected:
		DBConnection<iConnection> *connection;
	public:
		virtual bool doesExist(int id) = 0;
		virtual std::vector<User> getByID(std::vector<int> id) = 0;
		virtual bool update(std::vector<User> users) = 0;
		virtual bool put(std::vector<User> users) = 0;
		virtual std::vector<User> getChatMembers(ChatRoom chat) = 0;
		virtual std::vector<User> getSender(Message mes) = 0;
};

class iChatRepo{
	protected:
		DBConnection<iConnection> *connection;
	public:
		virtual bool doesExist(int id) = 0;
		virtual std::vector<ChatRoom> getByID(std::vector<int> id) = 0;
		virtual bool update(std::vector<ChatRoom> chats) = 0;
		virtual bool put(std::vector<ChatRoom> chats) = 0;
		virtual bool addUserToChat(const ChatRoom &chat, const User &user) = 0;
		virtual ChatRoom getMesChat(Message mes) = 0;
		virtual std::vector<ChatRoom> getUserChats(User user) = 0;
};

class iMessageRepo{
	protected:
		DBConnection<iConnection> *connection;
	public:
		virtual bool doesExist(int id) = 0;
		virtual std::vector<iMessage> getByID(std::vector<int> id) = 0;
		virtual bool update(std::vector<iMessage> mes) = 0;
		virtual bool put(std::vector<iMessage> mes) = 0;
		virtual std::vector<iMessage> getFromRange(int start, int end,const ChatRoom &chat) = 0;
};

//Declaration block
class UserRepo: public iUserRepo{
	public:
		UserRepo(){};
		UserRepo(*DBConnection){};
		bool doesExist(int id);
		std::vector<User> getByID(std::vector<int> id);
		bool update(std::vector<User> users);
		bool put(std::vector<User> users);
		std::vector<User> getChatMembers(ChatRoom chat);
		std::vector<User> getSender(Message mes);
};

class ChatRepo: public iChatRepo{
	public:
		ChatRepo(){};
		ChatRepo(*DBConnection){};
		bool doesExist(int id);
		std::vector<ChatRoom> getByID(std::vector<int> id);
		bool update(std::vector<ChatRoom> chats);
		bool put(std::vector<ChatRoom> chats);
		bool addUserToChat(const ChatRoom &chat, const User &user);
		ChatRoom getMesChat(Message mes);
		std::vector<ChatRoom> getUserChats(User user);
};

class MessageRepo: public iMessageRepo{
	public:
		MessageRepo(){};
		MessageRepo(*DBConnection){};
		bool doesExist(int id);
		std::vector<iMessage> getByID(std::vector<int> id);
		bool update(std::vector<iMessage> mes);
		bool put(std::vector<iMessage> mes);
		std::vector<iMessage> getFromRange(int start, int end,const ChatRoom &chat);
};

/*
class InputRepo: public DBRepo{
	private:
		DBConnection *connection;
	public:
		bool doesExist(int id);
		Input* getByID(int id[], int len);
		bool update(Inputs inputs[], int len);
		bool put(Inputs inputs[], int len);
		Inputs* getInputs(Message mes);
};
*/

#endif