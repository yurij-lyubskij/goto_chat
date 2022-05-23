#include "client.h"

Client::Client() {
    mid = new Middleware(this);
}

Client::~Client() {
    delete mid;
}

void Client::open_chat(const std::string &chat_name) {

}

void Client::create_chat(const std::string &owner, const std::string &chat_name) {
//    new_chat(owner,chat_name);
}

void Client::delete_from_chat(const std::string &person_name) {
//    delete_person_from_chat(person_name);//функция Рината
}

void Client::leave_chat(const std::string &chat_name) {
//    leave_from_chat(chat_name);//функция Рината
}

void Client::reload_chat(const std::string &login, const std::string &chat_name) {

}

void Client::send_message(const std::string &chat_name, const std::string &text) {
    mid->send(chat_name, text);
}

bool Client::person_exist(const std::string &login) {
//    return check_person(login); //функция Рината
    return false;
}

bool Client::registrate(const std::string &first_name, const std::string &second_name, const std::string &login,
                        const std::string &password, const std::string &email) {
//    bool f = person_exist(login);
//    if(f){
//        reg_person(first_name, second_name, login,password, email);//функция Рината
//    }
//    return f;
    return true;
}

void Client::logout(const std::string &login) {
//    person_logout(login); //функция Рината
}

bool Client::sign_in(const std::string &login, const std::string &password) {
//    bool f = check_person(login, password); //функция Рината
//    return f;
    return true;
}
