// Created by RIskhakov1
#include <string>

#ifndef MESSAGE_H
#define MESSAGE_H

struct MessageData
{
    std::string TextMes;
    std::string ImageMes;
    std::string AudioMes;
    std::string CmdMes;
};

class iMessage
{
public:
    virtual ~iMessage() = default;

    virtual std::string Serialize(MessageData) = 0;

    virtual MessageData Deserialize(std::string) = 0;

    virtual void Format() = 0;
};

class Message : public iMessage
{
public:
    virtual std::string Serialize(MessageData) override;

    virtual MessageData Deserialize(std::string) override;

    virtual void Format() override;
};

#endif MESSAGE_H