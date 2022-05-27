#include "client.h"
#include "structures.h"

int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    client.sign_in(phone, password);
    Chat chat = client.create_chat("somechat", {"12345", "5", "956"});
    std::cout << chat.Id << " " << chat.chatName << std::endl;

    //client.sign_in(phone, password);
    client.logout();
    return EXIT_SUCCESS;
}
