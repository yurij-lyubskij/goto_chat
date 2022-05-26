#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>

class Parser {
public:
    //send methods
    static std::string create_session(const std::string &login, const std::string &password);

    static std::string create_user(const std::string &username, const std::string &phone, const std::string &password);

    static std::string
    create_chat(const std::string &chat_name, const std::string &phone1, const std::string &phone2);

    static std::string chat_join(const std::string &chatId, const std::string &phone);

    static std::string message(const std::string &chat_name, const std::string &text, const std::string &phone);

    //get methods
    static std::vector <std::string> chats(const std::string &chats_file);
};

#endif
