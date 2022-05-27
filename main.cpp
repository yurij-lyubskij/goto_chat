#include "client.h"
#include "structures.h"
//struct State {
//    virtual ~State();
//    virtual void up();
//    virtual void down();
//};
//class Machine;
//struct OFF : State {
//    void on(Machine *m);
//};
//struct ON : State {
//    void off(Machine *m);
//};
//class Machine {
//    State *m_State;
//public:
//    Machine() { m_State = new OFF(); }
//    void setCurrent(State *s) { m_State = s; }
//    void on() { m_State->on(this); }
//    void off() { m_State->off(this); }
//};

//{ std::cout << " going from OFF to ON"; m->setCurrent(new ON()); delete this; }
//{ cout << " going from ON to OFF"; m->setCurrent(new OFF()); delete this; }

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
    Chat chat = client.create_chat("somechat", {"12345", "475789", "456"});
    std::cout << chat.Id << " " << chat.chatName << std::endl;

    sleep(1);
    name = "voice.mp3";
//    client.getVoice(name);
    client.sendVoice(name, "1");
    return EXIT_SUCCESS;
}
