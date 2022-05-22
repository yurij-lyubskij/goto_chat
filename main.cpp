#include "Listener.h"
#include "Context.h"


int main() {
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8080);

    net::io_context ioc{1};
    tcp::socket mysock {ioc};
    std::shared_ptr<iRouter> router (new Router);
    std::shared_ptr<iMiddle> checkAuth(new CheckAuth);
    router->AddMiddle(checkAuth);
    std::shared_ptr<iHandler> createUser(new CreateNewUser);
    router->AddHandler(createUser);
    std::shared_ptr<iHandler> login(new Login);
    router->AddHandler(login);
    std::shared_ptr<iHandler> logout(new Logout);
    router->AddHandler(logout);
    std::shared_ptr<iSocket> sock (new Socket(mysock));
    std::shared_ptr<iBufferFabric> fabric (new BufferFabric);
    auto listener = std::make_shared<Listener>(
            sock, ioc, tcp::endpoint{address, port},
            router, fabric);
    listener->run();
    // Run the I/O service in Server
    std::shared_ptr<iContext> cont(new Context(ioc));
    printf("all is well\n");
    cont->run();
    printf("server is not running\n");

    return 0;
}
