#include "client.h"
//#include "request.h"

Client::Client()
{
}

Client::~Client()
{
}

void Client::send_request(http::request<http::file_body>&& request)
{
//    std::shared_ptr<session> ptr = std::make_shared<session>(ioc);
//    ptr->run(request);
//    ioc.run();
//    handle_response(ptr->get_response());
}

void Client::send_message(const std::string &chat_name, const std::string &text, const std::string &phone)
{
    /*beast::http::request<http::string_body> request = Request::message();
    request.body() = Parser::message(chat_name, text, phone);
    request.prepare_payload();
    send_request(request);*/
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
    std::string file_path = Parser::create_user(login, email, password);
    // send file with path = file_path
    // accept ok or not
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
