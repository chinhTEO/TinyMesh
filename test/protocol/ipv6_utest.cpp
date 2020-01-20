#include "ipv6.h"
#include <gtest/gtest.h> 

TEST(ipv6_utest, ipv6addr_cmp){
    IPV6_ADDR addr_1;
    IPV6_ADDR addr_2;
    IPV6_ADDR addr_3;
    
    memcpy(&addr_1, "12345678", 8);
    memcpy(&addr_2, "12345678", 8);
    memcpy(&addr_3, "10305070", 8);

    EXPECT_EQ(ipv6addr_cmp(&addr_1, &addr_2), true);
    EXPECT_EQ(ipv6addr_cmp(&addr_1, &addr_3), false);
}