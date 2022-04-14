//
// Created by yura11011 on 14.04.2022.
//

#ifndef GOTO_CHAT_HANDLER_H
#define GOTO_CHAT_HANDLER_H

class iHandler {
public:
    virtual ~iHandler() = default;

    virtual void CanHandle() = 0;

    virtual void Handle() = 0;
};

class Handler : public iHandler {
public:
    void CanHandle() override;
    void Handle() override;
};



#endif //GOTO_CHAT_HANDLER_H
