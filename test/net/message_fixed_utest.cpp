#include <gtest/gtest.h>
#include "tydebug.h"
#include "message_fixed.h"
#include "message_define.h"
#include "tyheap.h"

class message_fixed_utest: public ::testing::Test {
    protected: 
        virtual void SetUp( ) {
            memset(MEMBLOCK, 0, sizeof(unsigned char)*SIZE_OF_HEAP); 
            tyheap_init();
        }

        virtual void TearDown( ) {
            memset(MEMBLOCK, 0, sizeof(unsigned char)*SIZE_OF_HEAP); 
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
        }

};

TEST_F(message_fixed_utest, message_fixed_create){
    char data[] = "hello";
    struct Message_out *message_packet = (struct Message_out *)message_fixed_create(MESSAGE_UTEST_FIXED, (uint8_t *)data, HIGH_PRIORITY);
    EXPECT_EQ(message_packet->priority, HIGH_PRIORITY);
    EXPECT_EQ(message_packet->length, message_fixed_list[MESSAGE_UTEST_FIXED].length + 1);
    EXPECT_EQ(message_packet->headerRequirement, message_fixed_list[MESSAGE_UTEST_FIXED].headerRequirement);

    uint8_t header = (uint8_t)(MESSAGE_UTEST_FIXED << 1 | FIXED);
    EXPECT_EQ(message_packet->data[0], header);
    for(int i = 0; i < message_fixed_list[MESSAGE_UTEST_FIXED].length; i++){
        EXPECT_EQ(message_packet->data[i+1], data[i]);
    }
}

TEST_F(message_fixed_utest, message_fixed_proccess){
    uint8_t testMessage[7];
    memcpy(&testMessage[1], "hello", 6);
    testMessage[0] = (uint8_t)(MESSAGE_UTEST_FIXED << 1 | FIXED);
    EXPECT_EQ(message_fixed_proccess(testMessage), 7);
}