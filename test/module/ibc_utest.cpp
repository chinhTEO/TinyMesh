#include <gtest/gtest.h>
#include "tydebug.h"
#include "message.h"
#include "tyheap.h"
#include "message_define.h"
#include "ibc.h"
#include "frame_header.h"
#include "env_variable.h"
#include "tymesh_framer.h"

class ibc_utest: public ::testing::Test {
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

TEST_F(ibc_utest, ibc_send){
    char hello_msg[] = "hello world";
    ibc_send((uint8_t *)hello_msg, 12);
}

TEST_F(ibc_utest, ibc_callback){
    unsigned short len;
    memcpy(&IPV6_UUID, "12345678", 8);
    memset(&RECV_IPV6_UUID, '9', 8);

    for(int i = 0; i < 8; i++){
        EXPECT_NE(IPV6_UUID.u8[i], RECV_IPV6_UUID.u8[i]);
    }

    char hello_msg[] = "hello world";
    ibc_send((uint8_t *)hello_msg, 12); 

    uint8_t *frame = tymesh_framer_create(&len);
    std::cout << " this is : " << len << std::endl;
    tymesh_framer_process(frame, len);

    for(int i = 0; i < 8; i++){
        EXPECT_EQ(IPV6_UUID.u8[i], RECV_IPV6_UUID.u8[i]);
    }
}