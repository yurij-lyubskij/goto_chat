//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_MIDDLEWARE_H
#define GOTO_CHAT_MIDDLEWARE_H


class iMiddle {
public:
    virtual ~iMiddle() = default;

    virtual void CanHandle() = 0;

    virtual void Handle() = 0;
};

class CheckAuth : public iMiddle {
public:
    void CanHandle() override;

    void Handle() override;
};


#endif //GOTO_CHAT_MIDDLEWARE_H
