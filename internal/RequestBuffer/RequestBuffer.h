//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_REQUESTBUFFER_H
#define GOTO_CHAT_REQUESTBUFFER_H
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

class RequestBuffer {
// The buffer for performing reads.
public:
    beast::flat_buffer buff{8192};
};

#endif //GOTO_CHAT_REQUESTBUFFER_H
