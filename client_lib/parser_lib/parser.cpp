#include "parser.h"

std::string Parser::message(const std::string &chat_name, const std::string &text, const std::string &phone) {
    // {
    //     "chatId": "chat_name",
    //     "message":
    //     {
    //         "userPhone": "phone",
    //         "text": "text"
    //     }
    // }
    std::string filename = "./message.json";
    nlohmann::json json;
    json["chatId"] = chat_name;
    json["message"]["userPhone"] = phone;
    json["message"]["text"] = text;
    json["message"]["time"] = text;

    std::ofstream stream(filename);
    stream << json;
    stream.close();
    return filename;
}

std::string
Parser::create_chat(const std::string &chat_name, const std::string &phone1, const std::string &phone2) {
    std::string filename = "./new_chat.json";
    nlohmann::json json;
    json["chat_name"] = chat_name;
    json["users_count"] = 2;
    json["users"].push_back(phone1);
    json["users"].push_back(phone2);

    std::ofstream stream(filename);
    stream << json;
    stream.close();
    return filename;
}

std::string Parser::chat_join(const std::string &chatId, const std::string &phone) {
    std::string filename = "./add_person.json";
    nlohmann::json json;
    json["chatId"] = chatId;
    json["user"] = phone;

    std::ofstream stream(filename);
    stream << json;
    stream.close();
    return filename;
}

std::string Parser::create_session(const std::string &login, const std::string &password) {
    std::string filename = "./sign_in.json";
    nlohmann::json json;
    json["login"] = login;
    json["password"] = password;

    std::ofstream stream(filename);
    stream << json;
    stream.close();
    return filename;
}

std::string Parser::create_user(const std::string &username, const std::string &phone, const std::string &password) {
    std::string filename = "./new_user.json";
    nlohmann::json json;
    json["username"] = username;
    json["password"] = password;
    json["phone"] = phone;

    std::ofstream stream(filename);
    stream << json;
    stream.close();
    return filename;
}

//in use
std::vector <Chat> Parser::chats(const std::string &chats) {
    nlohmann::json json;
    std::stringstream stream(chats);
    stream >> json;
    std::vector <Chat> res;
    for (nlohmann::json chat: json["chats"]) {
        Chat ch({chat["id"], chat["chatName"]});
        res.push_back(ch);
    }
    return res;
}

class MessageComparator{
	public:
		MessageComparator(){};
		bool operator()(const Message &first, const Message &second){
			return std::stoi(first.Id) < std::stoi(second.Id);
		};
};
//in use
std::vector <Message> Parser::messages(const std::string &messages){
    std::stringstream stream(messages);
    
    nlohmann::json json;
    stream >> json;
    std::vector <Message> res;
    for (nlohmann::json message: json["messages"]) {
        Message mes({message["id"],
                    message["text"],
                    message["userPhone"],
                    message["time"],
                    (message["type"] == "text")? text : voice});
        res.push_back(mes);
    }
    std::sort(res.begin(), res.end(), MessageComparator());
    return res;
}
