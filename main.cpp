#include "client.h"
#include "structures.h"

int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    client.sign_in(phone, password);

    std::vector<Message> messages = client.getLastMessages("3");
    for (Message mes : messages){
        std::cout << mes.Id << " " << mes.text << " " << mes.time << " " << mes.phone << " " << mes.type << " " << std::endl;
    }
    //client.sign_in(phone, password);
    client.logout();
    return EXIT_SUCCESS;
}
