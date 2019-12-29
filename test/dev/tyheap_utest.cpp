#include <gtest/gtest.h>
#include "tyheap.h"
#include <iostream>

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
    uint16_t block = 0;
    block = 2;
    block = block << 2;
    block = block | 1;  //busy

    ASSERT_EQ(mem[0], (block & 0x00ff));
    ASSERT_EQ(mem[1], block >> 8);

    //test second block header
    block = 0;
    block = tyheap_sizeOfHeap() - tyheap_sizeOfHeader();
    block = block << 2;
    block = block | 0; //free
    
    ASSERT_EQ(mem[2], (block & 0x00ff));
    ASSERT_EQ(mem[3], block >> 8);

    block = 0;
    block = block << 2;
    block = block | 1; //busy

    ASSERT_EQ(mem[tyheap_sizeOfHeap() - tyheap_sizeOfHeader()],     (block & 0x00ff));
    ASSERT_EQ(mem[tyheap_sizeOfHeap() - tyheap_sizeOfHeader() + 1], block >> 8);
}


