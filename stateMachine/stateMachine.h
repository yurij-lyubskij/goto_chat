//
// Created by yura11011 on 27.05.22.
//

#ifndef GOTO_CHAT_STATEMACHINE_H
#define GOTO_CHAT_STATEMACHINE_H
class Machine;
struct State {
    virtual ~State() = default;
    virtual void up(Machine *m) = 0;
    virtual void down(Machine *m) = 0;
};


struct unAuthorised : State {
    void up(Machine *m);
    void down(Machine *m);
};

struct inMain : State {
    void up(Machine *m);
    void down(Machine *m);
};

struct inChat : State {
    void up(Machine *m);
    void down(Machine *m);
};

class Machine {
    State *m_State;
public:
    Machine() { m_State = new unAuthorised(); }
    void setCurrent(State *s) { m_State = s; }
    void on() { m_State->up(this); }
    void off() { m_State->down(this); }
};

void unAuthorised::up(Machine *m) {

}

void unAuthorised::down(Machine *m) {

}

void inMain::up(Machine *m) {

}

void inMain::down(Machine *m) {

}

void inChat::up(Machine *m) {

}

void inChat::down(Machine *m) {

}
//{ std::cout << " going from OFF to ON"; m->setCurrent(new ON()); delete this; }
//{ cout << " going from ON to OFF"; m->setCurrent(new OFF()); delete this; }
#endif //GOTO_CHAT_STATEMACHINE_H
