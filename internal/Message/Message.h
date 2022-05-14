#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <time.h>

#include "User.h"

enum MessegeType{ textMessage, voiceMessage };

class iMessage{
	protected:
		int id;
		time_t sendTime;
		std::string content;
		int senderId;
		enum MessegeType type;
	public:
		int getId() const { return id; };
		int getSender() const { return senderId; };
		time_t getTime() const { return sendTime; };
		std::string getContent() const { return content; };
		enum MessegeType getType() const { return type; };
};

class Message: public iMessage{
	protected:
	public:
		Message();													//Creates empty(false) object
		Message(int);
		Message(std::string, time_t, int);							//Creates object with id = 0 to add to database
		Message(int, std::string, time_t, int);
		Message(const Message&);
		Message operator=(const Message&);

};

class VoiceMessage: public iMessage{
	protected:
	public:
		VoiceMessage();													//Creates empty(false) object
		VoiceMessage(int);
		VoiceMessage(std::string, time_t, int);							//Creates object with id = 0 to add to database
		VoiceMessage(int, std::string, time_t, int);
		VoiceMessage(const VoiceMessage&);
		VoiceMessage operator=(const VoiceMessage&);
};

#endif