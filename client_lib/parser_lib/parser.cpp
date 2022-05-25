#include "parser.h"

std::string Parser::message(const std::string &chat_name, const std::string &text,  const std::string &phone) {
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
    return filename;
}