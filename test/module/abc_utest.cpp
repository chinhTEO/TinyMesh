#include <gtest/gtest.h>
#include "tydebug.h"
#include "message.h"
#include "tyheap.h"
#include "message_define.h"
#include "abc.h"
#include "frame_header.h"
#include "env_variable.h"
#include "tymesh_framer.h"

class abc_utest: public ::testing::Test {
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

TEST_F(abc_utest, abc_send){
    char hello_msg[] = "hello world";
    abc_send((uint8_t *)hello_msg, 12);
}

TEST_F(abc_utest, abc_callback){
    unsigned short len;

    char hello_msg[] = "hello world";
    abc_send((uint8_t *)hello_msg, 12); 

    uint8_t *frame = tymesh_framer_create(&len);
    std::cout << " this is : " << len << std::endl;
    tymesh_framer_process(frame, len);
}