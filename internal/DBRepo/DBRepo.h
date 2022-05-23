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
/*
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
*/
enum DBObjectType { user, chat, message, input };

enum DBOperation { checkIt, putIt, deleteIt, updateIt, getFew,
																								//user spec operations
					addMembers, removeMembers/*, getMessageOrigin*/, getChatsofUser, findWithName,	//chat spec operations
					getRange																	//message spec operations
};

typedef struct{
	DBOperation operation;
    DBObjectType objectType;
    std::string request;
} DBRequest;

class DBObject{
    public:
        DBObjectType type;
        std::vector<std::string> attr;
        DBObject();
		DBObject(const DBObject&);
		~DBObject();
        DBObject(const User&);
        DBObject(const ChatRoom&);
        DBObject(const iMessage&);
		operator User();
		operator ChatRoom();
		operator iMessage();
		DBObject operator=(const DBObject&);
        //DBObject(InputDB);        
};

class iConnection{
    public:
        virtual std::vector<DBObject> exec(DBRequest, std::vector<DBObject>) = 0;
        virtual std::vector<DBObject> get(DBRequest) = 0;
	protected:
		std::vector<std::string> split(const std::string&);
};


//PostgreSQL connection
class PGConnection: public iConnection{
    private:
		time_t convertTimeStamp(char*);
		std::vector<DBObject> checkUsers(std::vector<DBObject>);
		std::vector<DBObject> checkChats(std::vector<DBObject>);
		std::vector<DBObject> checkMessages(std::vector<DBObject>);
		std::vector<DBObject> putUsers(std::vector<DBObject>);
		std::vector<DBObject> putChats(std::vector<DBObject>);
		std::vector<DBObject> putMessages(std::vector<DBObject>);
		std::vector<DBObject> addMembersToChat(std::vector<DBObject>);
		std::vector<DBObject> getUsersById(std::vector<std::string>);
		std::vector<DBObject> getChatsById(std::vector<std::string>);
		std::vector<DBObject> getMessagesById(std::vector<std::string>);
		std::vector<DBObject> getMembers(DBObject);
		std::vector<DBObject> getUserChats(DBObject);
		std::vector<DBObject> getMessagesFromRange(int, int, int);
		std::vector<DBObject> getChatsByName(std::string);
        //void establish_connection();
		//actual connections settings
        std::shared_ptr<PGconn>  m_connection;

		std::string m_dbhost = "localhost";
    	int         m_dbport = 5432;
		std::string m_dbname = "gotochatdatabase";
    	std::string m_dbuser = "postgres";
    	std::string m_dbpass = "postgres";
		//table and columns names
		const std::string usersTableName = 			"users";
			const std::string userIdCol = 				"us_id";
			const std::string userNameCol = 			"us_name";
			const std::string userPhoneCol = 			"us_phone";
			const std::string userPasswordeCol = 			"us_password";
		const std::string chatsTableName = 			"chats";
			const std::string chatIdCol = 				"ch_id";
			const std::string chatNameCol = 			"ch_name";
		const std::string usersChatsTableName = 	"users_chats";
		const std::string messagesTableName = 		"messages";
			const std::string messageIdCol = 			"ms_id";
			const std::string messageTimeCol = 			"ms_sendTime";
		const std::string textInputsTableName = 	"textinputs";
			const std::string textInputIdCol = 			"tip_id";
			const std::string textInputContentCol = 	"tip_content";
		const std::string voiceInputsTableName =	"voiceinputs";
			const std::string voiceInputIdCol = 		"vip_id";
			const std::string voiceInputContentCol = 	"vip_content";
		const std::string inputsTableName = 		"inputs";
			const std::string inputsIdCol = 			"ip_id";
			const std::string inputTypeCol = 			"ip_type";
   	public:
    	PGConnection();
		std::vector<DBObject> exec(DBRequest, std::vector<DBObject>) override;
        std::vector<DBObject> get(DBRequest) override;
    	//std::shared_ptr<PGconn> connection() const;
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
		virtual std::vector<int> put(std::vector<ChatRoom> chats) = 0;
		virtual bool addUsersToChat(const ChatRoom &chat, std::vector<User> users) = 0;
		virtual bool removeUsersFromChat(const ChatRoom &chat, std::vector<User> users) = 0;
		virtual std::vector<ChatRoom> findByName(std::string) = 0;
		//virtual ChatRoom getMesChat(Message mes) = 0;
		virtual std::vector<ChatRoom> getUserChats(const User& user) = 0;
};

class iMessageRepo{
	protected:
		DBConnection<iConnection> *connection;
	public:
		virtual bool doesExist(int id) = 0;
		virtual std::vector<iMessage> getByID(std::vector<int> id) = 0;
		virtual bool update(std::vector<iMessage> mes) = 0;
		virtual std::vector<int> put(std::vector<iMessage> mes) = 0;
		virtual std::vector<iMessage> getFromRange(int start, int end,const ChatRoom &chat) = 0;
};
/*
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
*/
class ChatRepo: public iChatRepo{
	public:
		ChatRepo();
		ChatRepo(DBConnection<iConnection>*);
		bool doesExist(int id) override;
		std::vector<ChatRoom> getByID(std::vector<int> id) override;
		bool update(std::vector<ChatRoom> chats) override;
		std::vector<int> put(std::vector<ChatRoom> chats) override;
		bool addUsersToChat(const ChatRoom &chat, std::vector<User> users) override;
		bool removeUsersFromChat(const ChatRoom &chat, std::vector<User> users) override;
		std::vector<ChatRoom> findByName(std::string) override;
		//ChatRoom getMesChat(Message mes);
		std::vector<ChatRoom> getUserChats(const User& user) override;
};

class MessageRepo: public iMessageRepo{
	public:
		MessageRepo();
		MessageRepo(DBConnection<iConnection>*);
		bool doesExist(int id) override;
		std::vector<iMessage> getByID(std::vector<int> id) override;
		bool update(std::vector<iMessage> mes) override;
		std::vector<int> put(std::vector<iMessage> mes) override;
		std::vector<iMessage> getFromRange(int start, int end,const ChatRoom &chat) override;
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