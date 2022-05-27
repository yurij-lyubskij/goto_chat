#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "structures.h"

#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <sstream>


class Parser {
public:
    //send methods
    static std::string create_session(const std::string &login, const std::string &password);

    static std::string create_user(const std::string &username, const std::string &phone, const std::string &password);

    static std::string chat_create(const std::string &chat_name, std::vector<std::string> phones);

    static std::string chat_join(const std::string &chatId, const std::string &phone);

    static std::string message(const std::string &chat_name, const std::string &text, const std::string &phone);

    static std::string chat_id(const std::string &chat);

    //get methods
    static std::vector<Chat> chats(const std::string &chats);

    static std::vector<Message> messages(const std::string &chats_file);
};

#endif
