#include "parser.h"

Parser::Parser(Middleware *m) : mid(m)
{
}

http::request<http::string_body> Parser::send_message(const std::string &chat_name, const std::string &text)
{
    http::request<http::string_body> request;
    request.method(http::verb::post);
    request.target("/chat/message/send");
    request.body() = "{\"chatId\":\"" + chat_name + "\",\"message\":\"" + text + "\"}";
    request.prepare_payload();
    return request;
}
