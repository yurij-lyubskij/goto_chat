#ifndef PARSER_H
#define PARSER_H

#include <iostream>

class Parser
{
public:
    static std::string message(const std::string &chat_name, const std::string &text, const std::string &phone);
};

#endif