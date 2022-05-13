#include "Server.h"
#include "Listener.h"


class Context : public iContext {
public:
    Context(net::io_context &ioc) : ioc(ioc) {};

    void run() {
        ioc.run();
    };
private:
    net::io_context &ioc;
};

int main() {
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8080);

    // The io_context is required for all I/O
    net::io_context ioc{1};
    tcp::socket mysock {ioc};
    std::shared_ptr<Socket> sock (new Socket(mysock));
    std::shared_ptr<iAcceptor> acceptor(new Acceptor(ioc, tcp::endpoint{address, port}));
    std::make_shared<Listener>(
            sock,
            acceptor)->run();
    // Run the I/O service in Server
//    ioc.run();
    std::shared_ptr<iContext> cont(new Context(ioc));
    Server server = Server(cont);
    printf("all is well\n");
    server.Run();
    return 0;
}
