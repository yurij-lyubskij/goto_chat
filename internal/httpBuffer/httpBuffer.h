//
// Created by yura11011 on 13.05.22.
//

#ifndef GOTO_CHAT_HTTPBUFFER_H
#define GOTO_CHAT_HTTPBUFFER_H
#include "Request.h"
#include "Response.h"


class IhttpBuffer  {

public:
    virtual Request createRequest() = 0;

    virtual void createResponse(Response response) = 0;
    virtual void createFileResponse(Response response) = 0;
    virtual void contentLength() = 0;
    virtual ~IhttpBuffer() = default;
};

class httpBuffer : public IhttpBuffer  {

public:
    httpBuffer(){
        parser.body_limit(std::numeric_limits<std::uint64_t>::max());
    }
    // The buffer for performing reads.
    beast::flat_buffer buff{8192};
    // The request message.
    http::request<http::dynamic_body> request_;
    http::request_parser<http::dynamic_body>parser;
    // The response message.
    http::response<http::string_body> response_;

    http::response<http::file_body> fileResponse;
    Request createRequest() override {
        Request req;
        req.parameters["<field_name>"] = static_cast<std::string> (parser.get()["<field_name>"]);
        req.method = static_cast<std::string>(parser.get().method_string());
        auto cookies = parser.get()[http::field::cookie];
        req.cookie = static_cast<std::string>(cookies.substr(cookies.find("=") + 1));
        req.target = static_cast<std::string>(parser.get().target());
        req.body = beast::buffers_to_string(parser.get().body().data());
        return req;
    }
    void contentLength() override{
        response_.content_length(response_.body().size());
        fileResponse.content_length(fileResponse.body().size());
    }

    void createResponse(Response response) override {
        response_.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response_.set(http::field::content_type, "text/plain");
        response_.set(http::field::cookie, response.cookie);
        response_.keep_alive(false);
        response_.body() = response.body;
        response_.result(response.statusCode);
        response_.set("Set-Cookie", response.cookie);
    }

    void createFileResponse(Response response) override {
        http::response<http::file_body> res{
                std::piecewise_construct,
                std::make_tuple(std::move(response.file_body)),
                std::make_tuple(http::status::ok, parser.get().version())};
        fileResponse = std::move(res);
        fileResponse.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        fileResponse.set(http::field::content_type, "audio/mpeg");
        fileResponse.set(http::field::cookie, response.cookie);
        fileResponse.keep_alive(false);
        fileResponse.result(response.statusCode);
        fileResponse.set("Set-Cookie", response.cookie);
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
