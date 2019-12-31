#include <gtest/gtest.h>
#include "tyheap.h"
#include <iostream>

class tyheap_utest: public ::testing::Test {
    protected: 
        virtual void SetUp( ) { 
            tyheap_init();
        }

        virtual void TearDown( ) { 
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
        }

};

TEST_F(tyheap_utest, header_size){
    ASSERT_EQ(sizeof(struct Header),2);
}

TEST_F(tyheap_utest, tyheap_init){
    struct Header *testBlock = (struct Header *)&MEMBLOCK[0];
    ASSERT_EQ(testBlock->status, END);
    ASSERT_EQ(testBlock->next, 0);
}

TEST_F(tyheap_utest, DATA_SIZE_OF_){
    unsigned char memblock[11];
    struct Header *testBlock = (struct Header *)memblock;
    testBlock->status = FREE;
    testBlock->next = 10;

    //structure [status][nextindex][data  ] 
    //          [ 2bit ][ 14 bit  ][ nbit ]
    //  
    ASSERT_EQ(DATA_SIZE_OF_(testBlock), 10 - sizeof(struct Header));
}

TEST_F(tyheap_utest, DATA_ADDR_OF_){
    unsigned char memblock[11];
    struct Header *testBlock = (struct Header *)memblock;
    testBlock->status = FREE;
    testBlock->next = 10;

    //structure [status][nextindex][data  ] 
    //          [ 2bit ][ 14 bit  ][ nbit ]
    //          [byte 0][byte 1   ][byte2     ]{pointer addr data here}      
    int dataPositionInblock = 2;
    ASSERT_EQ((unsigned char *)DATA_ADDR_OF_(testBlock),&memblock[2]);
}

TEST_F(tyheap_utest, IS_STATUS_){
    unsigned char memblock[11];
    struct Header *testBlock = (struct Header *)memblock;
    
    
    testBlock->status = FREE;
    testBlock->next = 10;
    ASSERT_EQ(IS_STATUS_(testBlock, FREE), true);
    ASSERT_EQ(IS_STATUS_(testBlock, BUSY), false);
}

TEST_F(tyheap_utest, NEXT_BLOCK_OF_){
    unsigned char memblock[20];
    // create two block next to each other

    struct Header *testBlock_1 = (struct Header *)memblock;
    testBlock_1->status = FREE;
    testBlock_1->next = 10;

    struct Header *testBlock_2 = (struct Header *)&memblock[10];
    testBlock_2->status = FREE;
    testBlock_2->next = 10;

    //structure [status][nextindex][data    ][next block           ] 
    //          [ 2bit ][ 14 bit  ][ nbit   ]
    //          [byte 0][byte 1   ][byte2->n][sizeofbeforeblock + 1] <--- {pointer next block here}

    ASSERT_EQ(NEXT_BLOCK_OF_(testBlock_1),testBlock_2);
}

TEST_F(tyheap_utest, SIZE_OF_){
    unsigned char memblock[11];
    struct Header *testBlock = (struct Header *)memblock;
    
    
    testBlock->status = FREE;
    testBlock->next = 10;
    ASSERT_EQ(SIZE_OF_(testBlock), 10);
}

TEST_F(tyheap_utest, END_BLOCK_ADDRESS){
    ASSERT_EQ(END_BLOCK_ADDRESS(), &MEMBLOCK[SIZE_OF_HEAP]);
}