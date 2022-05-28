#include <fstream>
#include "client.h"
#include "targetBuilder.h"
#include "parser.h"

const char* get = "GET";
const char* post = "POST";
const size_t OK = 200;

Client::Client()
{
    ioc;
}


Chat Client::create_chat(const std::string &chat_name, std::vector<std::string> members)
{
    std::string target = TargetBuilder::createChat();
    std::string body = Parser::chat_create(chat_name, members);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(post, target.c_str(), body.c_str(), cookie.c_str());
    ioc.run();

    if(result.statusCode == OK) return {Parser::chat_id(result.body), chat_name};
    else return Chat({"0", ""});
}

bool Client::join_chat(const std::string &chatId, const std::string &phone){
    std::string target = TargetBuilder::joinChat();
    std::string body = Parser::chat_join(chatId, phone);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(post, target.c_str(), body.c_str(), cookie.c_str());
    ioc.run();

    if(result.statusCode == OK) return true;
    else return false;
};

std::vector<Chat> Client::find_chats(const std::string& chat_name){
    std::string target = TargetBuilder::findChat(chat_name);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(get, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Chat> chats;
    if(result.statusCode != OK) return chats;

    return Parser::chats(result.body);
}

std::vector<Chat> Client::get_users_chats(const std::string& phone){
    std::string target = TargetBuilder::getUserChats(phone);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(get, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Chat> chats;
    if(result.statusCode != OK) return chats;

    return Parser::chats(result.body);
};

std::vector<Message> Client::get_next_messages(const std::string& mes_id){
    std::string target = TargetBuilder::messageListFromMes(mes_id, next);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(get, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Message> messages;
    if(result.statusCode != OK) return messages;

    return Parser::messages(result.body);
};

std::vector<Message> Client::get_last_messages(const std::string &mes_id){
    std::string target = TargetBuilder::messageListFromMes(mes_id, last);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(get, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Message> messages;
    if(result.statusCode != OK) return messages;

    return Parser::messages(result.body);
};

std::vector<Message> Client::get_last_chat_messages(const std::string &chat_id){
    std::string target = TargetBuilder::messageListFromEmptyChat(chat_id);
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(get, target.c_str(), "", cookie.c_str());
    ioc.run();
    std::vector<Message> messages;
    if(result.statusCode != OK) return messages;

    return Parser::messages(result.body);
};


bool Client::registerUser(const std::string &username, const std::string &phone, const std::string &password)
{
    auto const target = "/user/create";
    ioc.reset();
    Response result;
    std::string body = R"({"username": ")";
    body+= username;
    body += R"(", "phone": ")";
    body+= phone;
    body+= R"(", "password": ")";
    body+= password;
    body += R"("})";
    std::make_shared<session>(ioc, result)->run(post, target, body.c_str(), "");
    ioc.run();
    if (result.statusCode!= OK) {
        return false;
    }
    cookie = result.cookie;
    std::cout << cookie <<'\n';
    return true;
}

void Client::logout()
{
    auto const target = "/session/delete";
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->run(post, target, "", cookie.c_str());
    cookie = "";
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
    return true;
}

bool Client::getVoice(const std::string &name) {
    std::string  target = "/chat/message/getfile?name=";
    target +=  name;
    ioc.reset();
    Response result;
    std::string body ="";
    std::make_shared<session>(ioc, result)->run(post, target.c_str(), body.c_str(), cookie.c_str());
    ioc.run();
    if (result.statusCode!= OK) {
        return false;
    }
    std::ofstream fout(name, std::ios::binary);
    fout.write(result.body.c_str(), result.body.size());
    fout.close();
    std::cout <<"size = "<< result.body.size() << "\n";
    return true;
}

bool Client::sendVoice(const std::string &name, const std::string &id) {
    std::string  target = "/chat/message/voice/send";
    ioc.reset();
    Response result;
    std::make_shared<session>(ioc, result)->file_run(target.c_str(), name.c_str(), id.c_str(), cookie.c_str());
    ioc.run();
    if (result.statusCode!= OK) {
        return false;
    }
    return true;
}

bool Client::sendMessage(const std::string &chatId, const std::string &text, const std::string &phone) {
    std::string  target = "/chat/message/send";
    ioc.reset();
    Response result;
    std::string body =R"({"chatId": )";
    body += chatId;
    body +=R"(, "message": {"userPhone": ")";
    body += phone;
    body+= R"(", "text": ")";
    body += text;
    body += R"("}})";
    std::make_shared<session>(ioc, result)->run(post, target.c_str(), body.c_str(), cookie.c_str());
    ioc.run();
    if (result.statusCode!= OK) {
        return false;
    }
    return true;
}



