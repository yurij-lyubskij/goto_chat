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
//in use
std::string Parser::chat_create(const std::string &chat_name, std::vector<std::string> phones) {
    std::string body = "";
    nlohmann::json json;

    json["chatName"] = chat_name;
    json["usersCount"] = phones.size();
    for (std::string phone : phones)
        json["users"].push_back(phone);

    
    std::cout << body << std::endl;
    std::stringstream stream;
    stream << json;
    stream >> body;
    return body;
}

//in use
std::string Parser::chat_join(const std::string &chatId, const std::string &phone) {
    std::string body = "";
    nlohmann::json json;

    json["chatId"] = chatId;
    json["user"] = phone;

    std::stringstream stream;
    stream << json;
    stream >> body;
    return body;
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

std::string Parser::chat_id(const std::string &chat){
    std::stringstream stream(chat);
    
    nlohmann::json json;
    stream >> json;

    return std::to_string((int) json["chatId"]);
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
//in use
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


std::string Parser::get_text_from_message(const std::string &message)
{
    std::istringstream stream(message);
    std::string temp, result;
    stream >> temp;
    while (stream >> temp) {
        if(temp.front() != ':'){
            result+=temp;
        }
    }
    return result;
}

std::string Parser::get_message_from_Message(const Message &message)
{
    return message.phone + ": " + message.text + " :" + message.time;
}
