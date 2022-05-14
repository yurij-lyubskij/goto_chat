#include <gtest/gtest.h>


#include "reMessage.h"
#include "Message.h"
#include "DBRepo.h"

//Messages has the same approaching as ChatRoom so even though i didn't have the same problem
//I decided add tests to it as well
TEST(MessageTests, equatingTextMessage){
	{
	Message mes1(1, "text", 50, 1);
	Message mes2;
	mes2 = mes1;
	EXPECT_EQ(mes2.getId(), 1);
	EXPECT_EQ(mes2.getContent(), "text");
	EXPECT_EQ(mes2.getTime(), 50);
	EXPECT_EQ(mes2.getSender(), 1);
	}
	{
	Message mes1(2);
	Message mes2;
	mes2 = mes1;
	EXPECT_EQ(mes2.getId(), 2);
	EXPECT_EQ(mes2.getContent(), "");
	EXPECT_EQ(mes2.getTime(), 0);
	EXPECT_EQ(mes2.getSender(), 0);
	}
	{
	DBObject obj;
	Message mes3;
	obj.type = message;
	obj.attr = { "3" , "testText", "50", "1", "0" };
	mes3 = (iMessage) obj;
	EXPECT_EQ(mes3.getId(), 3);
	EXPECT_EQ(mes3.getContent(), "testText");
	EXPECT_EQ(mes3.getTime(), 50);
	EXPECT_EQ(mes3.getSender(), 1);
	}
}

TEST(MessageTests, equatingVoiceMessage){
	{
	VoiceMessage mes1(1, "/test/statics/voice", 50, 1);
	VoiceMessage mes2;
	mes2 = mes1;
	EXPECT_EQ(mes2.getId(), 1);
	EXPECT_EQ(mes2.getContent(), "/test/statics/voice");
	EXPECT_EQ(mes2.getTime(), 50);
	EXPECT_EQ(mes2.getSender(), 1);
	}
	{
	VoiceMessage mes1(2);
	VoiceMessage mes2;
	mes2 = mes1;
	EXPECT_EQ(mes2.getId(), 2);
	EXPECT_EQ(mes2.getContent(), "");
	EXPECT_EQ(mes2.getTime(), 0);
	EXPECT_EQ(mes2.getSender(), 0);
	}
	{
	DBObject obj;
	VoiceMessage mes3;
	obj.type = message;
	obj.attr = { "3" , "/statics/voice", "50", "1", "1" };
	mes3 = (iMessage) obj;
	EXPECT_EQ(mes3.getId(), 3);
	EXPECT_EQ(mes3.getContent(), "/statics/voice");
	EXPECT_EQ(mes3.getTime(), 50);
	EXPECT_EQ(mes3.getSender(), 1);
	}
}

TEST(MessageTests, downCast){
	iMessage iMes1(1, "test", 50, 1 , textMessage);
	iMessage iMes2(1, "/test/statics/voice", 50, 1 , voiceMessage);

	EXPECT_THROW({
        try
        {
            Message mes = iMes2;
        }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( e.what(),"the iMessage isn't text message" );
            throw;
        }
    }, std::invalid_argument );

	EXPECT_THROW({
        try
        {
            VoiceMessage mes = iMes1;
        }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( e.what(),"the iMessage isn't voice message" );
            throw;
        }
    }, std::invalid_argument );

	Message mes1 = iMes1;
	EXPECT_EQ(mes1.getId(), 1);
	EXPECT_EQ(mes1.getContent(), "test");
	EXPECT_EQ(mes1.getTime(), 50);
	EXPECT_EQ(mes1.getSender(), 1);

	VoiceMessage mes2 = iMes2;
	EXPECT_EQ(mes2.getId(), 1);
	EXPECT_EQ(mes2.getContent(), "/test/statics/voice");
	EXPECT_EQ(mes2.getTime(), 50);
	EXPECT_EQ(mes2.getSender(), 1);
}