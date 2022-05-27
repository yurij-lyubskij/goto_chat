#include "client.h"


int main()
{
    Client client;
    std::string phone = "12345";
    std::string password = "string";
    client.sign_in(phone, password);

    return EXIT_SUCCESS;
}
