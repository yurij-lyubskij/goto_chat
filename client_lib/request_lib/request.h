#include "boost/beast.hpp"

#ifndef REQUEST_H
#define REQUEST_H

namespace beast = boost::beast;
namespace http = beast::http;

class Request
{
public:
    Request() {}
    Request(const std::string& c) : cookie(c) {}

    http::request<http::file_body> message()
    {
        beast::http::request<http::file_body> request;
        request.method(http::verb::post);
        request.target("/chat/message/send");
        request.set("cookie", cookie);
        return request;
    }

private:
    std::string cookie;
};

#endif // REQUEST_H