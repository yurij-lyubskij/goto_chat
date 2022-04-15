//
// Created by yura11011 on 15.04.22.
//

#ifndef GOTO_CHAT_MESSAGEQUEUE_H
#define GOTO_CHAT_MESSAGEQUEUE_H

#include <queue>
#include <memory>

class iMessage{};

class iMessageQueue {
public:
    virtual ~iMessageQueue() = default;
    virtual void Push(std::shared_ptr<iMessage>) = 0;

    virtual std::shared_ptr<iMessage> Pop() = 0;
};

class MessageQueue :public iMessageQueue{
    std::queue<std::shared_ptr<iMessage>> messages;
public:
    void Push(std::shared_ptr<iMessage>) override;

    std::shared_ptr<iMessage> Pop() override;
};


#endif //GOTO_CHAT_MESSAGEQUEUE_H
