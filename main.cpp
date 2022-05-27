#include "client.h"
#include "structures.h"

int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    client.sign_in(phone, password);
    std::vector<Chat> chats = client.getUsersChats("56958");
    for (Chat chat : chats){
        std::cout << chat.Id << " " << chat.chatName << std::endl;
    }
    //client.sign_in(phone, password);
    client.logout();
    return EXIT_SUCCESS;
}
