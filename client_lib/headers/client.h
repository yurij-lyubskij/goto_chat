#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

#include "session.h"
#include "request.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;


class Client
{
public:
    Client();
    ~Client();

    void open_chat(const std::string &chat_name);

    void create_chat(const std::string &owner, const std::string &chat_name);

    void delete_from_chat(const std::string &person_name);

    void leave_chat(const std::string &chat_name);

    void reload_chat(const std::string &login, const std::string &chat_name);

    void send_message(const std::string &chat_name, const std::string &text, const std::string &phone);

    bool person_exist(const std::string &login);

    bool registrate(const std::string &first_name, const std::string &second_name,
                    const std::string &login, const std::string &password, const std::string &email);

    void logout(const std::string &user_name);

    bool sign_in(const std::string &login, const std::string &password);

private:
    void send_request(http::request<http::file_body>&& request);

    void handle_response(http::response<http::string_body> response)
    {
    }

    Request requestor;
    asio::io_context ioc;
};

#endif // CLIENT_H
