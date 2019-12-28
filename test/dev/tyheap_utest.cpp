#include <gtest/gtest.h>
#include "tyheap.h"

class tyheap_utest: public ::testing::Test {
    protected: 
        unsigned char *mem;
        virtual void SetUp( ) { 
            tyheap_init();
            mem = tyheap_MEMBLOCK();
        }

        virtual void TearDown( ) { 
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
        }
};

TEST_F(tyheap_utest, header_size){
    ASSERT_EQ(tyheap_sizeOfHeader(),2);
}

TEST_F(tyheap_utest, tymesh_init){
    //test first block header 
    ASSERT_EQ(mem[0], 0b00001001);
    ASSERT_EQ(mem[1], 0b00000000);

    //test second block header
    ASSERT_EQ(mem[2], 0b00000000);
    ASSERT_EQ(mem[3], 0b00000000);
}


