#ifndef GOTO_CHAT_MESSAGEQUEUE_H
#define GOTO_CHAT_MESSAGEQUEUE_H

#include <queue>
#include <memory>

#include "Message.h"

class iMessageQueue {
public:
    virtual ~iMessageQueue() = default;
    virtual void push(std::shared_ptr<iMessage>) = 0;

    virtual std::shared_ptr<iMessage> pop() = 0;
};

class MessageQueue :public iMessageQueue{
    std::queue<std::shared_ptr<iMessage>> messages;
public:
    void push(std::shared_ptr<iMessage>) override;

    std::shared_ptr<iMessage> pop() override;
};


#endif //GOTO_CHAT_MESSAGEQUEUE_H