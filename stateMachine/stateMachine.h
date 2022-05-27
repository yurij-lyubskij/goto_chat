//
// Created by yura11011 on 27.05.22.
//

#ifndef GOTO_CHAT_STATEMACHINE_H
#define GOTO_CHAT_STATEMACHINE_H
#include "client.h"

class Machine;
struct State {
    virtual ~State() = default;
    virtual void up(Machine *m) = 0;
    virtual void down(Machine *m) = 0;
    virtual void actionList() = 0;
};


struct unAuthorised : State {
    void up(Machine *m) override;
    void down(Machine *m) override;
    void actionList() override;
};

struct inMain : State {
    void up(Machine *m) override;
    void down(Machine *m) override;
    void actionList() override;
};

struct inChat : State {
    void up(Machine *m) override;
    void down(Machine *m) override;
    void actionList() override;
};

class Machine {
    State *m_State;
    Client client;
public:
    Machine(bool& isActive): isActive(isActive) {
        m_State = new unAuthorised();
    }
    void setCurrent(State *s) { m_State = s; }
    void listActions() {
        m_State->actionList();
    }
    void handleAction() {

    }
    void up() {
        m_State->up(this);
    }
    void down() {
        m_State->down(this);
    }

    bool& isActive;
};

void unAuthorised::up(Machine *m) {
    m->isActive = false;
}

void unAuthorised::down(Machine *m) {
    m->setCurrent(new inMain());
    delete this;
}

void unAuthorised::actionList() {
    std::cout << "to login press a\n";
    std::cout << "to register press d\n";
}

void inMain::up(Machine *m) {
    m->setCurrent(new unAuthorised);
    delete this;
}

void inMain::down(Machine *m) {
    m->setCurrent(new inChat);
    delete this;
}

void inMain::actionList() {
    std::cout << "to goto chat press d\n";
    std::cout << "to create chat press f\n";
    std::cout << "to join chat press a\n";
    std::cout << "to find chats press s\n";
    std::cout << "to log out press w\n";
}

void inChat::up(Machine *m) {
    m->setCurrent(new inMain());
    delete this;
}

void inChat::down(Machine *m) {

}

void inChat::actionList() {
    std::cout << "to read latest press d\n";
    std::cout << "to read more press f\n";
    std::cout << "to send message press a\n";
    std::cout << "to send file press s\n";
    std::cout << "to goto main press w\n";
}

#endif //GOTO_CHAT_STATEMACHINE_H
