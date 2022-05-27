#include "client.h"


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
    sleep(1);
    name = "voice.mp3";
    client.getVoice(name);
    return EXIT_SUCCESS;
}
