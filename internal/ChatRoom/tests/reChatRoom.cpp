#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "reChatRoom.h"
#include "ChatRoom.h"
#include "../WebSocketServer/tests/reWebSocketServer.h"

TEST(ChatTests, reaction){
	reWebSocketServer serv;
	ChatRoom chat(1);
	Message mes("abc", 50, 12);
	
	EXPECT_CALL(serv, addToQueue(testing::_)).Times(1);
	
	EXPECT_TRUE(chat.reactOn(mes));
}