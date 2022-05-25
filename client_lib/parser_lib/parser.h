#include <iostream>

#ifndef PARSER_H
#define PARSER_H

#include "middleware.h"

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = asio::ip::tcp;

class Parser
{
public:
    Parser(Middleware *m);
    ~Parser();

    http::request<http::string_body> send_message(const std::string &chat_name, const std::string &text);

private:
    Middleware *mid;
    std::string cookie;
};

#endif