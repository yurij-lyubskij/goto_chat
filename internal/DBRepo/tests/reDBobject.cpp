#include <gtest/gtest.h>
#include <iostream>

#include "DBRepo.h"
#include "User.h"
#include "ChatRoom.h"
#include "Message.h"

TEST(DBOBjectConverting, UserConverting){
	User usr;
	usr.Id = 1;
	DBObject object(usr);

	EXPECT_EQ(object.attr.size(), 3);
	EXPECT_EQ(object.attr[0], "1");
	EXPECT_EQ(object.attr[1], "");
	EXPECT_EQ(object.attr[2], "");


	usr.Name = "TestName";
	usr.PhoneNumber = "1234567890";
	object = DBObject(usr);
	EXPECT_EQ(object.attr[0], std::to_string(usr.Id));
	EXPECT_EQ(object.attr[1], usr.Name);
	EXPECT_EQ(object.attr[2], usr.PhoneNumber);

	DBObject toConvert;
	toConvert.type = chat;
	toConvert.attr = { "2" , "Name", "9087654321" };

	EXPECT_THROW({
        try
        {
            User usr2 = toConvert;
        }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( e.what(),"DBObject type isn't user" );
            throw;
        }
    }, std::invalid_argument );

	toConvert.type = user;
	User usr2 = toConvert;
	EXPECT_EQ(usr2.Id, 2);
	EXPECT_EQ(usr2.Name, "Name");
	EXPECT_EQ(usr2.PhoneNumber, "9087654321");
}

TEST(DBOBjectConverting, ChatRoomConverting){
	ChatRoom cht1(1);
	DBObject object(cht1);

	EXPECT_EQ(object.attr.size(), 2);
	EXPECT_EQ(object.attr[0], "1");
	EXPECT_EQ(object.attr[1], "");

	ChatRoom cht2(2, "Name");
	object = DBObject(cht2);
	EXPECT_EQ(object.attr[0], "2");
	EXPECT_EQ(object.attr[1], "Name");

	DBObject toConvert;
	toConvert.type = user;
	toConvert.attr = { "3" , "TestName" };

	EXPECT_THROW({
        try
        {
            ChatRoom cht3(toConvert);
        }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( e.what(),"DBObject type isn't chat" );
            throw;
        }
    }, std::invalid_argument );
	
	toConvert.type = chat;
	ChatRoom cht3(toConvert);
	EXPECT_EQ(cht3.getId(), 3);
	EXPECT_EQ(cht3.getName(), "TestName");
}

TEST(DBOBjectConverting, MessageConverting){
	Message mes1(1);
	DBObject object(mes1);

	EXPECT_EQ(object.attr.size(), 5);
	EXPECT_EQ(object.attr[0], "1");
	EXPECT_EQ(object.attr[1], "");
	EXPECT_EQ(object.attr[2], "0");
	EXPECT_EQ(object.attr[3], "0");
	EXPECT_EQ(object.attr[4], "0");

	Message mes2(2, "text", 50, 1);
	object = DBObject(mes2);
	EXPECT_EQ(object.attr[0], "2");
	EXPECT_EQ(object.attr[1], "text");
	EXPECT_EQ(object.attr[2], "50");
	EXPECT_EQ(object.attr[3], "1");
	EXPECT_EQ(object.attr[4], "0");

	DBObject toConvert;
	toConvert.type = user;
	toConvert.attr = { "3" , "TestText", "45", "2", "0" };
	
	EXPECT_THROW({
        try
        {
            iMessage mes3(toConvert);
        }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( e.what(),"DBObject type isn't message" );
            throw;
        }
    }, std::invalid_argument );

	toConvert.type = message;
	iMessage mes3(toConvert);
	EXPECT_EQ(mes3.getId(), 3);
	EXPECT_EQ(mes3.getContent(), "TestText");
	EXPECT_EQ(mes3.getTime(), 45);
	EXPECT_EQ(mes3.getSender(), 2);
	EXPECT_EQ(mes3.getType(), textMessage);
}
