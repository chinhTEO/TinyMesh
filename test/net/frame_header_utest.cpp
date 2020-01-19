#include <gtest/gtest.h> 
#include "frame_header.h"
#include "env_variable.h"

TEST(framer_header_utest, lengthOfHeader){
    int16_t headerCMD = HEADER_SELF_ADDRESS_IPV6 | HEADER_SELF_ADDRESS_SHORT | HEADER_FRAME_ID;
    EXPECT_EQ(lengthOfHeader(headerCMD), 14);
}

TEST(framer_header_utest, createHeader){
    int16_t headerCMD = HEADER_SELF_ADDRESS_IPV6 | HEADER_SELF_ADDRESS_SHORT | HEADER_FRAME_ID;
    uint8_t testBuffer[100];
    uint8_t validationBuffer[100];

    memset(testBuffer, 0, 100);
    
    uint8_t fakeIPV6[8]      = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t fakeShort[2]     = {9, 10};
    uint16_t fakeFrameHeader = 13499;

    memcpy(validationBuffer,        (uint8_t *)&headerCMD, 2);
    memcpy(&validationBuffer[2],     fakeIPV6, 8);
    memcpy(&validationBuffer[10],    fakeShort, 2);
    memcpy(&validationBuffer[12],    (uint8_t *)&fakeFrameHeader, 2);

    memcpy(IPV6_UUID,     fakeIPV6, 8);
    memcpy(SHORT_UUID,    fakeShort, 2);
    memcpy((uint8_t *)&FRAME_NUMBER,    (uint8_t *)&fakeFrameHeader, 2);

    EXPECT_EQ(createHeader(headerCMD, testBuffer), 14);

    for(int i = 0; i < 14; i++){
        EXPECT_EQ(testBuffer[i], validationBuffer[i]);
    }
}