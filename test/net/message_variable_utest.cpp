#include <gtest/gtest.h>
#include "tydebug.h"
#include "message_variable.h"
#include "message_define.h"
#include "tyheap.h"

class message_variable_utest: public ::testing::Test {
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

TEST_F(message_variable_utest, message_variable_create){
    char data[] = "hello";
    struct Message_out *message_packet = (struct Message_out *)message_variable_create(MESSAGE_UTEST_VARIABLE, (uint8_t *)data, 6, 200);
    EXPECT_EQ(message_packet->delay, 200);
    EXPECT_EQ(message_packet->length, 8);

    uint8_t header = (uint8_t)(MESSAGE_UTEST_VARIABLE << 1 | VARIABLE);

    EXPECT_EQ(message_packet->data[0], header);
    EXPECT_EQ(message_packet->data[1], 6);

    for(int i = 0; i < 6; i++){
        EXPECT_EQ(message_packet->data[i+2], data[i]);
    }
}

TEST_F(message_variable_utest, message_variable_proccess){
    uint8_t testMessage[8];
    memcpy(&testMessage[1], "hello", 6);

    testMessage[0] = (uint8_t)(MESSAGE_UTEST_VARIABLE << 1 | VARIABLE);
    testMessage[1] = 6;

    EXPECT_EQ(message_variable_proccess(testMessage), 8);
}