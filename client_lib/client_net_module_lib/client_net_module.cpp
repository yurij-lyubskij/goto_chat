#include "client_net_module.h"
#include "boost/asio.hpp"
#include <thread>
#include <iostream>

void fail(beast::error_code ec, char const *what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

NetModule::NetModule() : ioc(std::thread::hardware_concurrency() / 2),
                         resolver(asio::make_strand(ioc)), ws(asio::make_strand(ioc))
{
}

std::shared_ptr<NetModule> NetModule::Create()
{
    return std::shared_ptr<NetModule>(new NetModule);
}

void NetModule::Run(const std::string &host, const std::string &port)
{
    this->host = host;
    this->port = port;
    try
    {
        resolver.async_resolve(host, port, beast::bind_front_handler(&NetModule::OnResolve, shared_from_this()));
        ioc.run();
    }
    catch (beast::error_code ec)
    {
        return fail(ec, "run\n");
    }
}

void NetModule::OnResolve(beast::error_code ec, tcp::resolver::results_type results)
{
    if (ec)
    {
        return fail(ec, "resolve\n");
    }

    beast::get_lowest_layer(ws).expires_after(std::chrono::seconds(30));

    beast::get_lowest_layer(ws).async_connect(
        results,
        beast::bind_front_handler(
            &NetModule::OnConnect,
            shared_from_this()));
}

void NetModule::OnConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if (ec)
    {
        return fail(ec, "connect\n");
    }

    beast::get_lowest_layer(ws).expires_never();

    ws.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::client));

    ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type &req)
        {
            req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-async");
        }));

    host += ':' + std::to_string(ep.port());

    ws.async_handshake(host, "/",
                       beast::bind_front_handler(
                           &NetModule::OnHandshake,
                           shared_from_this()));
}

void NetModule::OnHandshake(beast::error_code ec)
{
    if (ec)
    {
        return fail(ec, "handshake\n");
    }

    threads.reserve(std::thread::hardware_concurrency() / 2);
    threads.emplace_back([&]()
                         {
                            Listen();
                            ioc.run(); });

    threads[0].detach();

    for (size_t i = 1; i < std::thread::hardware_concurrency() / 2; ++i)
    {
        threads.emplace_back([&]()
                             { ioc.run(); });
    }
}

void NetModule::Listen()
{
    ws.async_read(buf, beast::bind_front_handler(&NetModule::OnRead, shared_from_this()));
}

void NetModule::OnRead(beast::error_code ec, size_t bytes_transferred)
{
    if (ec)
    {
        return fail(ec, "read\n");
    }
    // Parse(buf);
    Listen();
}

void NetModule::Parse(beast::error_code ec, size_t bytes_transferred)
{
    if (ec)
    {
        //
    }
    //
}

void NetModule::Send(http::request<http::string_body> &req)
{
    //ws.async_write(req, beast::bind_front_handler(&NetModule::OnWriting, shared_from_this()));
    ioc.run();
}

void NetModule::OnWriting(beast::error_code ec, size_t bytes_transferred)
{
    if (ec)
    {
        return fail(ec, "writing");
    }
}

void NetModule::Disconnect()
{
    ws.async_close(websocket::close_code::normal, beast::bind_front_handler(&NetModule::OnClose, shared_from_this()));
}

void NetModule::OnClose(beast::error_code ec)
{
    if (ec)
    {
        return fail(ec, "disconnect\n");
    }

    ioc.stop();
}
