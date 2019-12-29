#include "tyheap.h"
#include <stdint.h>
#include <string.h>

//structure [status][nextindex][data  ] 
//          [ 2bit ][ 14 bit  ][ nbit ]

enum {
    FREE = 0,
    BUSY = 1
};

struct Header{
    unsigned char status : 2;
    uint16_t nextIndex : 14;
};

struct Block{
    struct Header block;
    uint16_t size;
};

#define NUMBER_OF_FREE_SLOT 5
#define INDEX_BLOCK_PTR(n)   ((struct Header *)&MEMBLOCK[n])

const uint16_t sizeList[NUMBER_OF_FREE_SLOT] = { 128, 64, 32, 16, 8 }; // free space Guarantee
struct Block freeBlockList[NUMBER_OF_FREE_SLOT];

unsigned char MEMBLOCK[SIZE_OF_HEAP];

void  tyheap_init( void ){
    //[firstblock][secondblock][data]
    // nextindex == 0 // last memory
    struct Header* firstBlock = (struct Header*)MEMBLOCK;
    struct Header* secondBlock;
    struct Header* lastBlock = INDEX_BLOCK_PTR(SIZE_OF_HEAP - sizeof(struct Header));
    
    firstBlock->status = BUSY;             //mark first block as busy
    firstBlock->nextIndex = 2;          //index to next block

    secondBlock = INDEX_BLOCK_PTR(firstBlock->nextIndex);
    secondBlock->status = FREE;
    secondBlock->nextIndex = SIZE_OF_HEAP - sizeof(struct Header); //i dont have next block, i am free

    lastBlock->status = BUSY;
    lastBlock->nextIndex = 0;

    memset(freeBlockList, 0, NUMBER_OF_FREE_SLOT*sizeof(struct Block)); // reset all slot in freeBlockList to 0
}

void *tyheap_malloc( size_t size ){

    return NULL;
}

void  tyheap_free( void *ptr ){

}

void  tyheap_organize(void ){
    struct Header* block = (struct Header*)MEMBLOCK;

    while(1){
        if(block->status == FREE){
            while(MEMBLOCK[block->nextIndex] == FREE){
                block->nextIndex = INDEX_BLOCK_PTR(block->nextIndex)->nextIndex;
            }
            // combine with next block if next block is free 
            // update cache free block
        }

        if(block->nextIndex != 0){
            block = (struct Header *)&MEMBLOCK[block->nextIndex];
        }else{
            break; // end of memory block
        }
    }
}


#ifdef UTEST

unsigned char *tyheap_MEMBLOCK(void){
    return MEMBLOCK;
}

unsigned int tyheap_sizeOfHeader(void){
    return sizeof(struct Header);
}

unsigned int tyheap_sizeOfHeap(void){
    return SIZE_OF_HEAP;
}

#endif