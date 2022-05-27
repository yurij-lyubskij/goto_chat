#include "client.h"
#include "structures.h"

int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    std::string name = "string1";
//    client.sign_in(phone, password);
//    client.logout();
//    sleep(1);
//    phone = "456";
//    client.registerUser(name, phone, password);
    client.sign_in(phone, password);
    Chat chat = client.create_chat("somechat", {"12345", "5", "956"});
    std::cout << chat.Id << " " << chat.chatName << std::endl;

    //client.sign_in(phone, password);
    client.logout();
    sleep(1);
    name = "voice.mp3";
//    client.getVoice(name);
    client.sendVoice(name, "1");
    return EXIT_SUCCESS;
}
