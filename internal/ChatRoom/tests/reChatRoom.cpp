#include <gtest/gtest.h>

#include "reChatRoom.h"
#include "ChatRoom.h"
#include "DBRepo.h"

//Had a problem with equating of this exact class in very specific cases so made a test with it to keep under control
TEST(ChatRoomTests, equating){
	{
	ChatRoom cht1(1, "name");
	ChatRoom cht2;
	cht2 = cht1;
	EXPECT_EQ(cht2.getId(), 1);
	EXPECT_EQ(cht2.getName(), "name");
	}
	{
	ChatRoom cht1(1);
	ChatRoom cht2;
	cht2 = cht1;
	EXPECT_EQ(cht2.getId(), 1);
	EXPECT_EQ(cht2.getName(), "");
	}
	{
	DBObject obj;
	ChatRoom cht3;
	obj.type = chat;
	obj.attr = { "1" , "testName" };
	cht3 = obj;
	EXPECT_EQ(cht3.getId(), 1);
	EXPECT_EQ(cht3.getName(), "testName");
	}
}