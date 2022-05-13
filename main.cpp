#include "Listener.h"
#include "Context.h"


int main() {
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8080);

    // The io_context is required for all I/O
    net::io_context ioc{1};
    tcp::socket mysock {ioc};
    std::shared_ptr<iSocket> sock (new Socket(mysock));
    std::shared_ptr<iAcceptor> acceptor(new Acceptor(ioc, tcp::endpoint{address, port}));
    std::make_shared<Listener>(
            sock,
            acceptor)->run();
    // Run the I/O service in Server
//    ioc.run();
    std::shared_ptr<iContext> cont(new Context(ioc));
    printf("all is well\n");
    cont->run();
    return 0;
}
