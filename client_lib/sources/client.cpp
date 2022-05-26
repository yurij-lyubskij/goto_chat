#include "client.h"
#include "parser.h"
#include "request.h"

Client::Client()
{
}

Client::~Client()
{
}

void Client::send_request(http::request<http::file_body>&& request)
{
    std::shared_ptr<session> ptr = std::move(std::make_shared<session>(ioc));
    ptr->run(std::move(request));
    ioc.run();
    handle_response(ptr->get_response());
}

void Client::send_message(const std::string &chat_name, const std::string &text, const std::string &phone)
{
    http::request<http::file_body> request = requestor.message();
    std::string filename = Parser::message(chat_name, text, phone);

    http::file_body::file_type file;
    beast::error_code ec;
    file.open(filename.c_str(), beast::file_mode::read, ec);

    http::request_parser<http::file_body> parser{std::piecewise_construct,
                                                 std::make_tuple(std::move(file))};

    ?

    request.prepare_payload();
    send_request(std::move(request));
}

void Client::open_chat(const std::string &chat_name)
{
}

void Client::create_chat(const std::string &owner, const std::string &chat_name)
{
    //    new_chat(owner,chat_name);
}

void Client::delete_from_chat(const std::string &person_name)
{
    //    delete_person_from_chat(person_name);//функция Рината
}

void Client::leave_chat(const std::string &chat_name)
{
    //    leave_from_chat(chat_name);//функция Рината
}

void Client::reload_chat(const std::string &login, const std::string &chat_name)
{
}

bool Client::person_exist(const std::string &login)
{
    //    return check_person(login); //функция Рината
    return false;
}

bool Client::registrate(const std::string &first_name, const std::string &second_name, const std::string &login,
                        const std::string &password, const std::string &email)
{
    //    bool f = person_exist(login);
    //    if(f){
    //        reg_person(first_name, second_name, login,password, email);//функция Рината
    //    }
    //    return f;
    return true;
}

void Client::logout(const std::string &login)
{
    //    person_logout(login); //функция Рината
}

bool Client::sign_in(const std::string &login, const std::string &password)
{
    //    bool f = check_person(login, password); //функция Рината
    //    return f;
    return true;
}
