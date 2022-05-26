#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "server_address.h"
#include "client.h"

namespace beast = boost::beast;        
namespace http = beast::http;    
namespace net = boost::asio;           
using tcp = boost::asio::ip::tcp;      


void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

class session : public std::enable_shared_from_this<session>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; 
    http::request<http::file_body> req_;
    http::response<http::string_body> res_;

public:
    http::response<http::string_body> get_response() {
        return res_;
    }


    explicit
    session(net::io_context& ioc)
            : resolver_(net::make_strand(ioc))
            , stream_(net::make_strand(ioc))
    {
    }

    void
    run(http::request<http::file_body>&& request)
    {
        req_ = std::move(request);

        resolver_.async_resolve(
                SERVER_IP,
                SERVER_PORT,
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

        stream_.expires_after(std::chrono::seconds(30));

        stream_.async_connect(
                results,
                beast::bind_front_handler(
                        &session::on_connect,
                        shared_from_this()));
    }

    void
    on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if(ec)
            return fail(ec, "connect");

        stream_.expires_after(std::chrono::seconds(30));

        http::async_write(stream_, req_,
                          beast::bind_front_handler(
                                  &session::on_write,
                                  shared_from_this()));
    }

    void
    on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        http::async_read(stream_, buffer_, res_,
                         beast::bind_front_handler(
                                 &session::on_read,
                                 shared_from_this()));
    }

    void
    on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "read");

        stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

        if(ec && ec != beast::errc::not_connected)
            return fail(ec, "shutdown");

    }
};