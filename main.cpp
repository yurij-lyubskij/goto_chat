#include "structures.h"
#include "stateMachine.h"


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
//    bool isActive = true;
//    Machine chat(isActive);
//
//    while (isActive) {
//        chat.listActions();
//        chat.handleAction();
//    }



    return EXIT_SUCCESS;
}
