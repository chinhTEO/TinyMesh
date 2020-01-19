#include <gtest/gtest.h>
#include "tymesh_framer.h"
#include "message_variable.h"
#include "message_fixed.h"
#include "message.h"
#include "tyheap.h"
#include "queue.h"

class tymesh_framer_utest: public ::testing::Test {
    protected: 
        virtual void SetUp( ) {
            memset(MEMBLOCK, 0, sizeof(unsigned char)*SIZE_OF_HEAP); 
            tyheap_init();
            tymesh_framer_init();
        }

        virtual void TearDown( ) {
            memset(MEMBLOCK, 0, sizeof(unsigned char)*SIZE_OF_HEAP); 
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
        }

};

TEST_F(tymesh_framer_utest, tymesh_framer_init) {
    tymesh_framer_init();
}

TEST_F(tymesh_framer_utest, tymesh_framer_add){
    char data[] = "hello";
    struct Message_out *message_packet = (struct Message_out *)message_fixed_create(MESSAGE_UTEST_FIXED, (uint8_t *)data, HIGH_PRIORITY);
    tymesh_framer_add(message_packet);
    EXPECT_EQ(queue_size(&highPriorityMessageList), 1);
    EXPECT_EQ(queue_size(&lowPriorityMessageList), 0);
    struct Message_out *message_packet_1 = (struct Message_out *)message_variable_create(MESSAGE_UTEST_VARIABLE, (uint8_t *)data, 6, LOW_PRIORITY);
    tymesh_framer_add(message_packet_1);
    EXPECT_EQ(queue_size(&highPriorityMessageList), 1);
    EXPECT_EQ(queue_size(&lowPriorityMessageList), 1);
}

TEST_F(tymesh_framer_utest, tymesh_framer_create) {
    char data[] = "hello";
    unsigned short len;
    struct Message_out *message_packet = (struct Message_out *)message_fixed_create(MESSAGE_UTEST_FIXED, (uint8_t *)data, HIGH_PRIORITY);
    struct Message_out *message_packet_1 = (struct Message_out *)message_variable_create(MESSAGE_UTEST_VARIABLE, (uint8_t *)data, 6, HIGH_PRIORITY);
    tymesh_framer_add(message_packet);
    tymesh_framer_add(message_packet_1);
    uint8_t *out_str = tymesh_framer_create(&len);

    EXPECT_EQ(len, 17);

    uint8_t header = (uint8_t)(MESSAGE_UTEST_FIXED << 1 | FIXED);
    EXPECT_EQ(message_packet->data[0], header);
    for(int i = 0; i < message_fixed_list[MESSAGE_UTEST_FIXED].length; i++){
        EXPECT_EQ(out_str[i+1+2], data[i]);
    }

    header = (uint8_t)(MESSAGE_UTEST_VARIABLE << 1 | VARIABLE);

    EXPECT_EQ(out_str[7 + 2], header);
    EXPECT_EQ(out_str[8 + 2], 6);

    for(int i = 0; i < 6; i++){
        EXPECT_EQ(out_str[i+7+2+2], data[i]);
    }

    tymesh_framer_process(out_str, 17);
}