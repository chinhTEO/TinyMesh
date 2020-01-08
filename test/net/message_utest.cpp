#include <gtest/gtest.h>
#include "tydebug.h"
#include "message.h"
#include "tyheap.h"
#include "message_define.h"

class message_utest: public ::testing::Test {
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

TEST_F(message_utest, getTypeOfMessage) {
    uint8_t test_FIXED =    (uint8_t)FIXED;
    uint8_t test_VARIABLE = (uint8_t)VARIABLE;

    EXPECT_EQ(getTypeOfMessage(&test_FIXED),    FIXED);
    EXPECT_EQ(getTypeOfMessage(&test_VARIABLE), VARIABLE);
}

TEST_F(message_utest, message_process){
    uint8_t testMessage_fixed[7];
    testMessage_fixed[0] = (uint8_t)(MESSAGE_UTEST_FIXED << 1 | FIXED);
    memcpy(&testMessage_fixed[1], "hello", 6);
    EXPECT_EQ(message_process(testMessage_fixed), message_fixed_list[MESSAGE_UTEST_FIXED].length + 1);

    uint8_t testMessage_variable[8];
    testMessage_variable[0] = (uint8_t)(MESSAGE_UTEST_VARIABLE << 1 | VARIABLE);
    testMessage_variable[1] = 6;
    memcpy(&testMessage_variable[2], "hello", 6);
    EXPECT_EQ(message_process(testMessage_variable), 8);
}

TEST_F(message_utest, processMessageList){
    uint8_t testMessageList[7+8];

    //create fixed message
    testMessageList[0] = (uint8_t)(MESSAGE_UTEST_FIXED << 1 | FIXED);
    memcpy(&testMessageList[1], "hello", 6);

    //create variable message
    testMessageList[7] = (uint8_t)(MESSAGE_UTEST_VARIABLE << 1 | VARIABLE);
    testMessageList[8] = 6;
    memcpy(&testMessageList[9], "hello", 6);

    EXPECT_EQ(processMessageList(testMessageList, 15), 15);
}