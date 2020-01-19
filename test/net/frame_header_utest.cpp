#include <gtest/gtest.h> 
#include "frame_header.h"

TEST(framer_header_utest, lengthOfHeader){
    int16_t headerCMD = SELF_ADDRESS_IPV6 | SELF_ADDRESS_SHORT | FRAME_ID;
    EXPECT_EQ(lengthOfHeader(headerCMD), 12);
}
