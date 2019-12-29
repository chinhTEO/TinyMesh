#include "tyheap.h"
#include <stdint.h>
#include <string.h>

#ifdef DEBUG
    #include <stdio.h>
#endif

//structure [status][nextindex][data  ] 
//          [ 2bit ][ 14 bit  ][ nbit ]

enum {
    FREE = 0,
    BUSY = 1
};

enum {
    SPLIT_OK,
    SPLIT_OVERSIZE,
    SPLIT_BUSY,
    SPLIT_UNCHANGE  
};

struct Header{
    unsigned char status : 2;
    uint16_t nextIndex : 14;
};

#define INDEX_OF_PTR(ptr)           ((unsigned char *)ptr - MEMBLOCK)
#define SIZE_OF_BLOCK_PTR(ptr)      (ptr->nextIndex - INDEX_OF_PTR(ptr))
#define SIZE_OF_BLOCK_INDEX(index)  (((struct Header *)&MEMBLOCK[index])->nextIndex - index)
#define NUMBER_OF_FREE_SLOT     5
#define INDEX_BLOCK_PTR(index)      ((struct Header *)&MEMBLOCK[index])
#define BLOCK_MEM_PTR_INDEX(index)  ((void *)&MEMBLOCK[index + sizeof(struct Header)])
#define BLOCK_MEM_PTR_PTR(ptr)      (ptr + sizeof(struct Header))

const uint16_t sizeList[NUMBER_OF_FREE_SLOT] = { 128, 64, 32, 16, 8 }; // free space Guarantee
unsigned short freeBlockList[NUMBER_OF_FREE_SLOT];

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

    memset(freeBlockList, 0, NUMBER_OF_FREE_SLOT*sizeof(struct Header*)); // reset all slot in freeBlockList to 0
}

unsigned short split_block(unsigned short index, size_t size){
    struct Header *block = INDEX_BLOCK_PTR(index);
    struct Header *nblock;
    unsigned short current_block_size = block->nextIndex - index;

    if(block->status == BUSY){
        return SPLIT_BUSY;
    }

    if(current_block_size > size + sizeof(struct Header)*2 + 8){
        nblock = INDEX_BLOCK_PTR(index + size + sizeof(struct Header));
        nblock->nextIndex = block->nextIndex;
        nblock->status = FREE;

        block->nextIndex = index + size + sizeof(struct Header);
        return SPLIT_OK;
    }
    else if (current_block_size > size + sizeof(struct Header)){
        return SPLIT_UNCHANGE;
    }else{
        return SPLIT_OVERSIZE;
    }
}

void *tyheap_alloc( size_t size ){
    unsigned short i;
    unsigned short status;
    for(i = NUMBER_OF_FREE_SLOT - 1; i >= 0 ; i--){
        if(size < sizeList[i]){
            if(freeBlockList[i] != 0){
                status = split_block(freeBlockList[i], size);
                
                if(status == SPLIT_OK || status == SPLIT_UNCHANGE){
                    INDEX_BLOCK_PTR(freeBlockList[i])->status = BUSY;
                    return BLOCK_MEM_PTR_INDEX(freeBlockList[i]);
                }
            }
        }
    }
    return NULL;
}

void  tyheap_free( void *ptr ){
    struct Header *block = (struct Header *)(ptr - sizeof(struct Header));
    block->status = FREE;
}

void  tyheap_organize(void ){
    struct Header* block = (struct Header*)MEMBLOCK;
    unsigned short i;
    while(1){
        if(block->status == FREE){
            // combine with next block if next block is free 
            while(MEMBLOCK[block->nextIndex] == FREE){
                block->nextIndex = INDEX_BLOCK_PTR(block->nextIndex)->nextIndex;
            }

            // update cache free block
            for(i = 0; i < NUMBER_OF_FREE_SLOT ; i++){
                if(SIZE_OF_BLOCK_PTR(block) > sizeList[i]){
                    if(freeBlockList[i] != 0){
                        if(SIZE_OF_BLOCK_INDEX(freeBlockList[i]) >  SIZE_OF_BLOCK_PTR(block)){
                            freeBlockList[i] = INDEX_OF_PTR(block);
                        }
                    }else{
                            freeBlockList[i] = INDEX_OF_PTR(block);
                    }
                    break;
                }
            }
        }

        if(block->nextIndex != 0){
            block = (struct Header *)&MEMBLOCK[block->nextIndex];
        }else{
            break; // end of memory block
        }
    }
}
#if DEBUG

void tyheap_printmem(unsigned char size) {
    int i = 0;
    printf("---------------mem-----------------\n");
    for(i = 0; i < size; i++){
        printf("%x",MEMBLOCK[i]);
        if(i % 16 == 15){
            printf("\n");
        }else{
            printf(" | ");
        }
    }
    printf("---------------mem-----------------\n");
}

#endif

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