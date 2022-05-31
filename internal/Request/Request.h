//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_REQUEST_H
#define GOTO_CHAT_REQUEST_H

#include <map>
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

const int16_t OK = 200;
const int16_t UnAuthorized = 401;
const int16_t BadRequest = 400;
const int16_t NotFound = 404;
const int16_t Conflict = 409;

class Request {
public:
    Request() {
        responseStatus = OK;
    }

    std::vector<std::string> headers;
    std::string method;
    std::string cookie;
    std::string body;
    std::string target;
    int16_t responseStatus;
    std::map<std::string, std::string> parameters;
};


#endif //GOTO_CHAT_REQUEST_H
