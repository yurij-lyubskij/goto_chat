#include <gtest/gtest.h>
#include "client_net_module.h"
#include "message.h"

TEST(Message, Serialize)
{
    {
        Message mes;
        MessageData data{
            "some text"};
        std::string serialized;
        EXPECT_EQ(serialized, mes.Serialize(data));
    }
    {
        Message mes;
        MessageData data{
            "some audio"};
        std::string serialized;
        EXPECT_EQ(serialized, mes.Serialize(data));
    }
    {
        Message mes;
        MessageData data{
            "some pictures"};
        std::string serialized;
        EXPECT_EQ(serialized, mes.Serialize(data));
    }
    {
        Message mes;
        MessageData data{
            "some commands"};
        std::string serialized;
        EXPECT_EQ(serialized, mes.Serialize(data));
    }
    {
        Message mes;
        MessageData data{
            "some text",
            "some pictures"};
        std::string serialized;
        EXPECT_EQ(serialized, mes.Serialize(data));
    }
}

TEST(Message, Deserialize)
{
    {
        Message mes;
        MessageData data;
        std::string input;
        data = mes.Deserialize(input);
        EXPECT_EQ(data.TextMes, "some text");
    }
    {
        Message mes;
        MessageData data;
        std::string input;
        data = mes.Deserialize(input);
        EXPECT_EQ(data.AudioMes, "some audio");
    }
    {
        Message mes;
        MessageData data;
        std::string input;
        data = mes.Deserialize(input);
        EXPECT_EQ(data.ImageMes, "some pictures");
    }
    {
        Message mes;
        MessageData data;
        std::string input;
        data = mes.Deserialize(input);
        EXPECT_EQ(data.CmdMes, "some commands");
    }
    {
        Message mes;
        MessageData data;
        std::string input;
        data = mes.Deserialize(input);
        EXPECT_EQ(data.ImageMes, "some pictures");
        EXPECT_EQ(data.TextMes, "some text");
    }
}