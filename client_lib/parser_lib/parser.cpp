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

std::vector <Message> Parser::messages(const std::string &chats_file){
    std::ifstream stream(chats_file);
    nlohmann::json json;
    stream >> json;
    std::vector <Message> res;
    for (auto it: json["messages"]) {
        Message m;
        m.Id = it["id"];
        m.phone = it["userPhone"];
        m.text = it["text"];
        m.time = it["time"];
        res.push_back(m);
    }
    stream.close();
    return res;
}
