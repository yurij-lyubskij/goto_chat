#include <gtest/gtest.h>
#include "client.h"
#include "checker.h"

TEST(Client, Empty){
    Client cl;
    std::string str;
    cl.create_chat(str, str);
    cl.delete_from_chat(str);
    cl.leave_chat(str);
    cl.logout(str);
    cl.open_chat(str);
    cl.registrate(str, str, str, str, str);
    cl.reload_chat(str, str);
    //cl.send_message(str, str);

    EXPECT_TRUE(true);
}

TEST(Checker, strs_check){
    // password must be without ' ' (space symbol)
    EXPECT_FALSE(Checker::check_password("fsf fse"));
    EXPECT_TRUE(Checker::check_password("аффfse"));

    // name must have only rus or only en symbols
    EXPECT_FALSE(Checker::check_name("апвпfse"));
    EXPECT_TRUE(Checker::check_name("пвпа"));
    EXPECT_TRUE(Checker::check_name("sfdfd"));

    // email must have smth + @ + smth + . + smth
    EXPECT_TRUE(Checker::check_email("fsf@mai.ruuuuuuu"));
    EXPECT_FALSE(Checker::check_email("fsf@mai."));
    EXPECT_FALSE(Checker::check_email("@mai.es"));
    EXPECT_FALSE(Checker::check_email("dsvsobakamai.es"));
}

