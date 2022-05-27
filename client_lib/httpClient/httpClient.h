//
// Created by yura11011 on 27.05.22.
//

#ifndef GOTO_CHAT_HTTPCLIENT_H
#define GOTO_CHAT_HTTPCLIENT_H
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "Response.h"
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------



// Performs an HTTP GET and prints the response
class session : public std::enable_shared_from_this<session>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    http::request<http::string_body> req_;
    http::request<http::file_body> reqF;
    http::response<http::string_body> res_;
    Response& result;
    const char* host = "127.0.0.1";
    const char* port = "8080";
    void   fail(beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

public:
    // Objects are constructed with a strand to
    // ensure that handlers do not execute concurrently.
    explicit
    session(net::io_context& ioc, Response& result_)
            : resolver_(net::make_strand(ioc))
            , stream_(net::make_strand(ioc)), result(result_)
    {
    }

    // Start the asynchronous operation
    void
    run(    char const* method,
            char const* target,
            char const* body,
            const char* cookie
    )
    {
        // Set up an HTTP  request message
        req_.version(11);
        req_.method(http::verb::post);
        if (strcmp(method, "GET") == 0) {
            req_.method(http::verb::get);
        }
        req_.target(target);
        req_.set(http::field::host, host);
        req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req_.body() = body;
        if (strlen(cookie) > 0){
            std::string session = "session=";
            session += cookie;
            req_.set(http::field::cookie, session);
        }
        req_.prepare_payload();
        // Look up the domain name
        resolver_.async_resolve(
                host,
                port,
                beast::bind_front_handler(
                        &session::on_resolve,
                        shared_from_this()));
    }

    // Start the asynchronous operation for file transfer
    void
    file_run(
            char const* target,
            char const* name,
            char const* id,
            char const* cookie
    )
    {
        // Set up an HTTP  request message
        reqF.version(11);
        reqF.method(http::verb::post);
        reqF.target(target);
        reqF.set(http::field::host, host);
        reqF.set("id", id);
        reqF.set("name" , name);
        reqF.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        if (strlen(cookie) > 0){
            std::string session = "session=";
            session += cookie;
            reqF.set(http::field::cookie, session);
        }
        http::file_body::value_type file;
        beast::error_code ec;
        file.open(
                name,
                beast::file_mode::read,
                ec);
        std::cout << ec.message() << "\n";
        reqF.body() = std::move(file);
        reqF.prepare_payload();
        // Look up the domain name
        resolver_.async_resolve(
                host,
                port,
                beast::bind_front_handler(
                        &session::on_resolve,
                        shared_from_this()));
    }

    void
    on_resolve(
            beast::error_code ec,
            tcp::resolver::results_type results)
    {
        if(ec)
            return fail(ec, "resolve");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(100));

        // Make the connection on the IP address we get from a lookup
        stream_.async_connect(
                results,
                beast::bind_front_handler(
                        &session::on_connect,
                        shared_from_this()));
    }

    void    on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if(ec)
            return fail(ec, "connect");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        if (!reqF.body().is_open()) {
            // Send the HTTP request to the remote host
            http::async_write(stream_, req_,
                              beast::bind_front_handler(
                                      &session::on_write,
                                      shared_from_this()));
        } else {

            http::async_write(stream_, reqF,
                              beast::bind_front_handler(
                                      &session::on_write,
                                      shared_from_this()));
        }

    }

    void
    on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        // Receive the HTTP response
        http::async_read(stream_, buffer_, res_,
                         beast::bind_front_handler(
                                 &session::on_read,
                                 shared_from_this()));
    }

    void on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "read");

        // Write the message to result
        result.body = res_.body();
        auto cookies = res_[http::field::cookie];
        result.cookie = static_cast<std::string>(cookies);
        result.statusCode = res_.result_int();
        if (res_[http::field::content_type] != "text/plain") {
            result.isFile = true;
        }
        // Gracefully close the socket
        stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes so don't bother reporting it.
        if(ec && ec != beast::errc::not_connected)
            return fail(ec, "shutdown");

        // If we get here then the connection is closed gracefully
    }
};
#endif //GOTO_CHAT_HTTPCLIENT_H
