// Created by RIskhakov1

#include <string>
#include <vector>
#include <thread>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/noncopyable.hpp>

#ifndef CLIENT_NET_MODULE_H
#define CLIENT_NET_MODULE_H

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace http = beast::http;
using tcp = asio::ip::tcp;

class NetModule : public std::enable_shared_from_this<NetModule>
{
public:

    [[nodiscard]] static std::shared_ptr<NetModule> Create();

    void Run(const std::string &host, const std::string &port);

    void Send(http::request<http::string_body>&);

    void Disconnect();

private:
    NetModule();
    void OnResolve(beast::error_code, tcp::resolver::results_type);
    void OnConnect(beast::error_code, tcp::resolver::results_type::endpoint_type);
    void OnHandshake(beast::error_code);
    void Listen();
    void OnRead(beast::error_code, size_t);
    void Parse(beast::error_code, size_t);
    void OnClose(beast::error_code);
    void OnWriting(beast::error_code, size_t);
    asio::io_context ioc;
    tcp::resolver resolver;
    websocket::stream<beast::tcp_stream> ws;
    beast::flat_buffer buf;

    std::string host;
    std::string port;

    std::vector<std::thread> threads;
};

#endif
