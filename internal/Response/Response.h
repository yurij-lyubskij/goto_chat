//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_RESPONSE_H
#define GOTO_CHAT_RESPONSE_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <utility>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
typedef boost::beast::error_code error_code;

class Response {
public:
    Response():  isFile(false) , statusCode(200){};
    std::vector<std::string> headers;
    bool isFile;
    std::string cookie;
    std::string body;
    http::file_body::value_type file_body;
    int statusCode;
};

#endif //GOTO_CHAT_RESPONSE_H

