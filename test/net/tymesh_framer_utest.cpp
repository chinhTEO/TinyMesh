#include <gtest/gtest.h>
#include "tymesh_framer.h"
#include "message_variable.h"
#include "message_fixed.h"
#include "tyheap.h"
#include "queue.h"

class tymesh_framer_utest: public ::testing::Test {
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

TEST_F(tymesh_framer_utest, tymesh_framer_init){
    tymesh_framer_init();
}

TEST_F(tymesh_framer_utest, tymesh_framer_add){
    char data[] = "hello";
    struct Message_out *message_packet = (struct Message_out *)message_variable_create(MESSAGE_UTEST_VARIABLE, (uint8_t *)data, 6, HIGH_PRIORITY);
    tymesh_framer_add(message_packet);
    EXPECT_EQ(queue_size(&highPriorityMessageList), 1);
    EXPECT_EQ(queue_size(&lowPriorityMessageList), 0);
    struct Message_out *message_packet_1 = (struct Message_out *)message_variable_create(MESSAGE_UTEST_VARIABLE, (uint8_t *)data, 6, HIGH_PRIORITY);
    tymesh_framer_add(message_packet_1);
    EXPECT_EQ(queue_size(&highPriorityMessageList), 1);
    EXPECT_EQ(queue_size(&lowPriorityMessageList), 1);
}