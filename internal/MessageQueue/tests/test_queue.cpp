#include <gtest/gtest.h>

#include <MessageQueue.h>

TEST(queue, default) {
    std::shared_ptr<iMessage> msg = std::make_shared<iMessage>();
    MessageQueue mQueue;
    mQueue.Push(msg);
    auto retval = mQueue.Pop();
    EXPECT_EQ(msg, retval);
}