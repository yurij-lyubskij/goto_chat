#include "client.h"


int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    client.sign_in(phone, password);
    sleep(1);
    client.sign_in(phone, password);
    client.logout();
    return EXIT_SUCCESS;
}
