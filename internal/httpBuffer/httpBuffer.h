//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_HTTPBUFFER_H
#define GOTO_CHAT_HTTPBUFFER_H
#include "Request.h"
#include "Response.h"
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

#include <vector>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
typedef boost::beast::error_code error_code;

class IhttpBuffer  {

public:
    virtual Request createRequest() = 0;

    virtual void createResponse(Response response) = 0;

    virtual void contentLength() = 0;
    virtual ~IhttpBuffer() = default;
};

class httpBuffer : public IhttpBuffer  {

public:
    // The buffer for performing reads.
    beast::flat_buffer buff{8192};
    // The request message.
    http::request<http::string_body> request_;

    // The response message.
    http::response<http::string_body> response_;

    Request createRequest() override {
        Request req;
        req.parameters["<field_name>"] = static_cast<std::string> (request_["<field_name>"]);
        req.method = static_cast<std::string>(request_.method_string());
        req.cookie = static_cast<std::string>(http::param_list(request_[http::field::cookie]).begin()->second);
        req.target = static_cast<std::string>(request_.target());
        req.body = static_cast<std::string>(request_.body());
        return req;
    }
    void contentLength() override{
        response_.content_length(response_.body().size());
    }

    void createResponse(Response response) override {
        response_.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response_.set(http::field::content_type, "text/plain");
        response_.set(http::field::cookie, response.cookie);
        response_.keep_alive(false);
        response_.body() = response_.body();
        response_.result(response.statusCode);
    }
};

class iBufferFabric {
public:
    virtual ~iBufferFabric() = default;
    virtual std::shared_ptr<IhttpBuffer> make() = 0;
};

class BufferFabric : public iBufferFabric{
public:
     std::shared_ptr<IhttpBuffer> make() override{
         return std::shared_ptr<IhttpBuffer> (new httpBuffer);
    }
};

#endif //GOTO_CHAT_HTTPBUFFER_H
