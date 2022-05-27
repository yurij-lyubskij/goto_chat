#include "client.h"
#include "targetBuilder.h"

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

const char* get = "GET";
const char* post = "POST";
const size_t OK = 200;

Client::Client()
{
    ioc;
}


void Client::send_message(const std::string &chat_name, const std::string &text, const std::string &phone)
{
    /*beast::http::request<http::string_body> request = Request::message();
    request.body() = Parser::message(chat_name, text, phone);
    request.prepare_payload();
    send_request(request);*/
}

std::vector<Chat> Client::find_chats(const std::string &chat_name){
    std::string target = TargetBuilder::findChat(chat_name);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(post, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Chat> chats;
    if(result.statusCode != OK) return chats;

    rapidjson::Document d;
    const char* json = result.body.c_str();
    d.Parse(json);
    if(! d.HasMember("chats")) return chats;
    if(! d["chats"].IsArray()) return chats;
    const rapidjson::Value& chatsJson = d["chats"];
    for (rapidjson::SizeType i = 0; i < chatsJson.Size(); ++i){/*
        chats.push_back({chatsJson[i].GetString()});
        usr = usRepo.GetbyPhone(usersPh[i].GetString());

        if (usr.Id == 0) return response;

        usrs.push_back(usRepo.GetbyPhone(usersPh[i].GetString()));*/
    }
    return;
}

void Client::open_chat(const std::string &chat_name)
{
}

Chat Client::create_chat(std::vector<std::string> members, const std::string &chat_name)
{
    return {0, ""};//    new_chat(members,chat_name);
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
//    std::string file_path = Parser::create_user(login, email, password);
    // send file with path = file_path
    // accept ok or not
    return true;
}

void Client::logout()
{
    auto const target = "/session/delete";
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(post, target, "", cookie.c_str());
    std::cout << result.statusCode << '\n';
    ioc.run();
}

bool Client::sign_in(const std::string &phone, const std::string &password)
{
    auto const target = "/session/create";
    ioc.reset();
    Response result;
    std::string body = R"({"phone": ")";
    body += phone;
    body += R"(", "password": ")";
    body += password;
    body+= R"("})";
    std::make_shared<session>(ioc, result)->run(post, target, body.c_str(), "");
    ioc.run();
    if (result.statusCode!= OK) {
        return false;
    }
    cookie = result.cookie;
    std::cout << cookie <<'\n';
    return true;
}
