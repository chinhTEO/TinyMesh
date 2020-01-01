#include <gtest/gtest.h>
#include "tyheap.h"
#include "tydebug.h"
#include <iostream>

class tyheap_utest: public ::testing::Test {
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

TEST_F(tyheap_utest, header_size){
    ASSERT_EQ(sizeof(struct Header),2);
}

TEST_F(tyheap_utest, tyheap_init){
    struct Header *testBlock = (struct Header *)&MEMBLOCK[0];

    ASSERT_EQ(testBlock->status, END);
    ASSERT_EQ(testBlock->next, 0);

    ASSERT_EQ(END_NORMAL_SEG, (unsigned char *)&MEMBLOCK[1]);

    testBlock = (struct Header *)&MEMBLOCK[SIZE_OF_HEAP - sizeof(struct Header)];

    ASSERT_EQ(testBlock->status, END);
    ASSERT_EQ(testBlock->next, 0);

    ASSERT_EQ(START_FLASH_SEG, (unsigned char *)&MEMBLOCK[SIZE_OF_HEAP - sizeof(struct Header)]);
}

TEST_F(tyheap_utest, DATA_SIZE_OF_){
    unsigned char memblock[11];
    memset(memblock, 0, 11);
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
    memset(memblock, 0, 11);
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
    memset(memblock, 0, 20);
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

TEST_F(tyheap_utest, expandNormalSeg_no_overflow){
    struct Header *block = (struct Header *)MEMBLOCK;
    unsigned short status;

    status = expandNormalSeg(block, SIZE_OF_HEAP - sizeof(struct Header)*3);    

    EXPECT_EQ(status, SUCCESS);

    EXPECT_EQ(END_NORMAL_SEG + 1, START_FLASH_SEG);
}

TEST_F(tyheap_utest, expandNormalSeg_overflow){
    struct Header *block = (struct Header *)MEMBLOCK;
    unsigned short status;

    status = expandNormalSeg(block, SIZE_OF_HEAP - sizeof(struct Header)*3 + 1); // this overflow 1 byte 

    EXPECT_EQ(status, FAIL);
}

TEST_F(tyheap_utest, expandFlashSeg_no_overflow){
    struct Header *block;
    unsigned short status;

    status = expandFlashSeg(&block, SIZE_OF_HEAP - sizeof(struct Header)*3);

    EXPECT_EQ(START_FLASH_SEG, (unsigned char *)block);
    EXPECT_EQ((unsigned char *)NEXT_BLOCK_OF_(block), (unsigned char *)block + SIZE_OF_HEAP - sizeof(struct Header)*3 + sizeof(struct Header));
    EXPECT_EQ(status, SUCCESS);
}

TEST_F(tyheap_utest, expandFlashSeg_overflow){
    struct Header *block;
    unsigned short status;

    status = expandFlashSeg(&block, SIZE_OF_HEAP - sizeof(struct Header)*3 + 1); // overflow buy 1 byte

    EXPECT_EQ(status, FAIL);
}

TEST_F(tyheap_utest, sliptBlock){
    const unsigned short testMemSize = 62;
    struct Header *block;
    
    //---------------- test mem ----------------//
    // prepare virtual memory;
    unsigned char memblock[testMemSize];
    memset(memblock, 0, 62);
    // create 3 block 20 size each
    block = (struct Header *)&memblock[0];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock[20];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock[40];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock[60];
    block->status = END;
    block->next   = 0;
    //---------------- test mem ----------------//

    //---------------- validation mem ----------------//
    unsigned char memblock_var[testMemSize];
    memset(memblock_var, 0, 62);
    // create 4 block 20->10->10->20
    block = (struct Header *)&memblock_var[0];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock_var[20];
    block->status = FREE;
    block->next   = 10;

    block = (struct Header *)&memblock_var[30];
    block->status = FREE;
    block->next   = 10;

    block = (struct Header *)&memblock_var[40];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock_var[60];
    block->status = END;
    block->next   = 0;
    //---------------- validation mem ----------------//


    //----------- success test ----------------//

    //tydebug_printmem(memblock, 62); 

    block = (struct Header *)&memblock[20];

    unsigned short status = splitBlock(block, 8, 5);

    EXPECT_EQ(status, SUCCESS);

    for (int i = 0; i < testMemSize; ++i) {
        EXPECT_EQ(memblock[i], memblock_var[i]) << " differ at index " << i;
    }

    //tydebug_printmem(memblock, 62);
    //tydebug_printmem(memblock_var, 62);
   
    // ------------ fail test by overflow --------//
    block = (struct Header *)&memblock[40];

    status = splitBlock(block, 12, 5);  // overflow by just 1 byte

    EXPECT_EQ(status, FAIL);
}

TEST_F(tyheap_utest, findAvailableBlockBiggerThan){
    const unsigned short testMemSize = 62;
    const unsigned short successFindTestSize = 17;
    const unsigned short failFindTestSize = 30;
    unsigned short status;
    struct Header *block;
    struct Header *returnBlock;
    
    //---------------- test mem ----------------//
    // prepare virtual memory;
    unsigned char memblock[testMemSize];
    memset(memblock, 0, 62);
    // create 3 block 20 size each
    block = (struct Header *)&memblock[0];
    block->status = FREE;
    block->next   = 10;

    block = (struct Header *)&memblock[10];
    block->status = FREE;
    block->next   = 20;

    block = (struct Header *)&memblock[30];
    block->status = FREE;
    block->next   = 30;

    block = (struct Header *)&memblock[60];
    block->status = END;
    block->next   = 0;

    //tydebug_printmem(memblock, 62);
    //---------------- test mem ----------------//
    // success test//
    status = findAvailableBlockBiggerThan((struct Header *)&memblock[0], &returnBlock, successFindTestSize);

    EXPECT_EQ(status, SUCCESS);
    EXPECT_EQ(returnBlock, (struct Header *)&memblock[10]);

    //fail test//
    status = findAvailableBlockBiggerThan((struct Header *)&memblock[0], &returnBlock, failFindTestSize);

    EXPECT_EQ(status, FAIL);
    EXPECT_EQ(returnBlock, (struct Header *)&memblock[60]);
}

/**
 * @brief Construct a new test f object
 * we test create very first allocation to check
 */
TEST_F(tyheap_utest, tyheap_alloc_1){
    const unsigned short testDataSize = 8;

    //tyheap_printmem(100);
    unsigned char *allocNem = (unsigned char *)tyheap_alloc(testDataSize);
    //tyheap_printmem(100);
    

    EXPECT_EQ(allocNem, &MEMBLOCK[2]); 
    EXPECT_EQ(END_NORMAL_SEG, allocNem + testDataSize + 1);

    struct Header *block = (struct Header *)(allocNem - 2);
    
    EXPECT_EQ(block->status, BUSY);
    EXPECT_EQ(sizeof(struct Header) + testDataSize , block->next);
}
/**
 * @brief Construct a new test f object
 * now we alloca mutiple block for testing with what we expect
 * expand testing
 */
TEST_F(tyheap_utest, tyheap_alloc_2){
    const unsigned short testMemSize = 64;
    struct Header *block;

    unsigned char memblock[testMemSize];
    memset(memblock, 0, 62);
    // create 3 block 20 size each
    block = (struct Header *)&memblock[0];
    block->status = BUSY;
    block->next   = 10;

    block = (struct Header *)&memblock[10];
    block->status = BUSY;
    block->next   = 20;

    block = (struct Header *)&memblock[30];
    block->status = BUSY;
    block->next   = 30;

    block = (struct Header *)&memblock[60];
    block->status = END;
    block->next   = 0;

    unsigned char *allocNem = (unsigned char *)tyheap_alloc(8);
    
    allocNem = (unsigned char *)tyheap_alloc(18);
    allocNem = (unsigned char *)tyheap_alloc(28);

    for (int i = 0; i < testMemSize; ++i) {
        EXPECT_EQ(MEMBLOCK[i], memblock[i]) << " differ at index " << i;
    }
}

/**
 * @brief Construct a new test f object
 * test if alloction stop expand when meet START_FLASH_MEMa
 * 1/ is to check if memory sit nicely
 */
TEST_F(tyheap_utest, tyheap_alloc_3){
    unsigned char *allocMem = (unsigned char *)tyheap_alloc(50);
    allocMem = (unsigned char *)tyheap_alloc(SIZE_OF_HEAP - sizeof(struct Header)*4 - 50);
    
    EXPECT_EQ(END_NORMAL_SEG + 1, START_FLASH_SEG);
    //tyheap_printmem(100);
}

/**
 * @brief Construct a new test f object
 * test if alloction stop expand when meet START_FLASH_MEMa
 * 2/ is to check if memory tect overlap
 * here we will overflow by 1 byte only and it should return NULL
 */
TEST_F(tyheap_utest, tyheap_alloc_4){
    unsigned char *allocMem = (unsigned char *)tyheap_alloc(50);
    allocMem = (unsigned char *)tyheap_alloc(SIZE_OF_HEAP - sizeof(struct Header)*4 - 50 + 1); // overflow byte 1 byte
    
    EXPECT_EQ(allocMem, (unsigned char *)NULL);
    //tyheap_printmem(100);
}


/**
 * @brief Construct a new test f object
 * now we alloca mutiple block and the last block are tembloc 
 *  
 */
TEST_F(tyheap_utest, tyheap_alloc_tmp_1){
    const unsigned short testMemSize = 64;
    struct Header *block;
    unsigned char *allocNem;
    unsigned char **alloc_ptr;

    unsigned char memblock[testMemSize];
    memset(memblock, 0, 62);
    // create 3 block 20 size each
    block = (struct Header *)&memblock[0];
    block->status = BUSY;
    block->next   = 10;

    block = (struct Header *)&memblock[10];
    block->status = BUSY;
    block->next   = 20;

    block = (struct Header *)&memblock[30];
    block->status = TEMP;
    block->next   = 30;

    alloc_ptr = &allocNem;
    memcpy((unsigned char *)block + 30 - sizeof(void *), &alloc_ptr, sizeof(void *));

    block = (struct Header *)&memblock[60];
    block->status = END;
    block->next   = 0;

    allocNem = (unsigned char *)tyheap_alloc(8);
    
    allocNem = (unsigned char *)tyheap_alloc(18);
    allocNem = (unsigned char *)tyheap_tmp_alloc(28 - sizeof(void *), (void **)&allocNem);

    // tydebug_printmem(memblock, 62);
    // printf("size of void %ld \n", (unsigned long)sizeof(void *));
    // tyheap_printmem(100);

    for (int i = 0; i < testMemSize; ++i) {
        EXPECT_EQ(MEMBLOCK[i], memblock[i]) << " differ at index " << i;
    }
}