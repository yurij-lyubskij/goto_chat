#include <gtest/gtest.h>
#include "client.h"
#include "checker.h"

TEST(Client, Empty){
    Client cl;
    std::string str;
    cl.create_chat(str,str);
    cl.delete_from_chat(str);
    cl.leave_chat(str);
    cl.logout(str);
    cl.open_chat(str);
    cl.registrate(str,str,str,str,str);
    cl.reload_chat(str,str);
    cl.send_message(str,str);

    EXPECT_TRUE(true);
}

TEST(Checker, strs_check){

}

