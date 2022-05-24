#include "Listener.h"
#include "Context.h"
#include "ChatRoomHandler.h"
#include "DBRepo.h"


int main() {
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8080);
    net::io_context ioc{1};
    tcp::socket mysock {ioc};
    std::shared_ptr<DBConnection<PGConnection>> connections(new DBConnection<PGConnection>(4));
    std::shared_ptr<iRouter> router (new Router);
    std::shared_ptr<iAuthDb> auth (new AuthDb);
    std::shared_ptr<iUserRepo> repo (new UserRepo());
    std::shared_ptr<iMiddle> checkAuth(new CheckAuth(auth));
    std::shared_ptr<IjsonParser> parser(new jsonParser);
    router->AddMiddle(checkAuth);
    std::shared_ptr<iHandler> createUser(new CreateNewUser(auth, repo, parser));
    router->AddHandler(createUser);
    std::shared_ptr<iHandler> login(new Login(auth, repo, parser));
    router->AddHandler(login);
    std::shared_ptr<iHandler> logout(new Logout(auth, repo));
    router->AddHandler(logout);
    std::shared_ptr<iHandler> example(new Example);
    router->AddHandler(example);

    std::shared_ptr<iHandler> getMessage(new GetMessageFromChat((DBConnection<iConnection>*) connections.get()));
    router->AddHandler(getMessage);
    std::shared_ptr<iHandler> createChat(new CreateChatRoom((DBConnection<iConnection>*) connections.get()));
    router->AddHandler(createChat);
    std::shared_ptr<iHandler> joinChat(new JoinChatRoom((DBConnection<iConnection>*) connections.get()));
    router->AddHandler(joinChat);
    std::shared_ptr<iHandler> findChat(new FindChatRoom((DBConnection<iConnection>*) connections.get()));
    router->AddHandler(findChat);
    
    std::shared_ptr<iBufferFabric> fabric (new BufferFabric);
    std::shared_ptr<iAcceptor> acceptor(new Acceptor(ioc, tcp::endpoint{address, port}));
    std::make_shared<Listener>(
            std::move(mysock),
            acceptor, router, fabric)->run();
    // Run the I/O service in Server
    std::shared_ptr<iContext> cont(new Context(ioc));
    printf("all is well\n");
    cont->run();
    printf("server is not running\n");
    return 0;
}
