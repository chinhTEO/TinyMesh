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

TEST(message_fixed_utest, message_fixed_create){
    char data[] = "hello";
    struct Message_out *message_packet = (struct Message_out *)message_fixed_create(MESSAGE_UTEST_FIXED, (uint8_t *)data, 200);
}