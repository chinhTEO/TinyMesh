#include "tyheap.h"
#include <string.h>
#include <stdio.h>

#if DEBUG
    #include "tydebug.h"
#endif

#if !UTEST
#include <stdint.h>
#include <string.h>

//------------------------ expose start --------------------------//
enum {
    FREE = 0,
    BUSY = 1,
    TEMP = 2,
    END  = 3,
};

enum {
    FAIL,
    SUCCESS
};

enum {
    SPLIT_OK,
    SPLIT_OVERSIZE,
    SPLIT_BUSY,
    SPLIT_UNCHANGE  
};


//structure [status][nextindex][data  ] 
//          [ 2bit ][ 14 bit  ][ nbit ]
struct Header{
    unsigned char status : 2;
    uint16_t next: 14;
};

#define DATA_SIZE_OF_(ptr)           (((struct Header*)ptr)->next - sizeof(struct Header))
#define DATA_ADDR_OF_(ptr)           ((unsigned char *)ptr + sizeof(struct Header))
#define IS_STATUS_(block, _status)   (((struct Header*)block)->status == _status)
#define NEXT_BLOCK_OF_(ptr)          (struct Header*)((unsigned char *)ptr + ((struct Header*)ptr)->next)
#define SIZE_OF_(block)              (block->next)   
#define END_BLOCK_ADDRESS()          (MEMBLOCK + SIZE_OF_HEAP)
#define BLOCK_OF_DATA_ADDR_(ptr)      ((unsigned char*)ptr - sizeof(struct Header))

#define NUM_OF_FREE_BLOCK_CACHE     5
#define OFFSET_SPLIT_SIZE           5

//------------------------ expose end --------------------------//
#endif

unsigned char MEMBLOCK[SIZE_OF_HEAP];
unsigned char *START_FLASH_SEG; 
unsigned char *END_NORMAL_SEG;

const uint16_t sizeList[NUM_OF_FREE_BLOCK_CACHE] = { 128, 64, 32, 16, 8 }; // free space Guarantee
unsigned short freeBlockList[NUM_OF_FREE_BLOCK_CACHE];

void  tyheap_init( void ){
    //[firstblock][secondblock][data]
    // nextindex == 0 // last memory
    struct Header* block;

    block = (struct Header*)MEMBLOCK;
    block->status = END;
    block->next = 0;
    
    END_NORMAL_SEG   = (unsigned char*)block + 1;

    block = (struct Header*)&MEMBLOCK[SIZE_OF_HEAP - sizeof(struct Header)];
    block->status = END;
    block->next = 0;

    START_FLASH_SEG = (unsigned char*)block;
}

unsigned short findAvailableBlockBiggerThan(struct Header *startBlock, struct Header **returnBlock, size_t size){
    struct Header* block = startBlock;
    unsigned short status;
    while(1){
        if(IS_STATUS_(block, FREE)){
            if(DATA_SIZE_OF_(block) >= size){
                *returnBlock = block;
                status = SUCCESS;
                break;
            }
        }

        if(IS_STATUS_(block, END)){
            *returnBlock = block;
            status = FAIL;
            break;
        }else{
            block = NEXT_BLOCK_OF_(block);
        }
    }
    return status;
}

unsigned short expandNormalSeg(struct Header *block, size_t dataSize){
    //[HEADER][DATA SIZE][HEADER END]
    struct Header *endBlock;
    
    if((unsigned char *)block + dataSize + sizeof(struct Header)*2 <= START_FLASH_SEG){
        block->status = FREE;
        block->next   = sizeof(struct Header) + dataSize;

        endBlock = NEXT_BLOCK_OF_(block);
        endBlock->status = END; 

        END_NORMAL_SEG = (unsigned char *)endBlock + 1;

        return SUCCESS;
    }else{
        return FAIL;
    }
}

unsigned short expandFlashSeg(struct Header **startBlock, size_t dataSize){
    if(END_NORMAL_SEG + sizeof(struct Header) + dataSize < START_FLASH_SEG){
        *startBlock = (struct Header *)(START_FLASH_SEG - sizeof(struct Header) - dataSize);
        (*startBlock)->next = sizeof(struct Header) + dataSize;
        (*startBlock)->status = FREE;
        START_FLASH_SEG = (unsigned char *)*startBlock; 

        return SUCCESS;
    }else{
        return FAIL;
    }
}

unsigned short splitBlock(struct Header *block, size_t dataSize, unsigned short offset){
    struct Header *nblock;
    
    if(DATA_SIZE_OF_(block) >= sizeof(struct Header) + dataSize + offset) {
        nblock = (struct Header*)((unsigned char *)block + dataSize + sizeof(struct Header));

        nblock->next = SIZE_OF_(block) - sizeof(struct Header) - dataSize;
        nblock->status = FREE;

        block->next = sizeof(struct Header) + dataSize;
        return SUCCESS;
    }else{
        return FAIL;
    }
}

unsigned short combineFreeBlock(struct Header *startBlock){
    struct Header *block = startBlock;
    struct Header *nblock;
    unsigned short totalDataSize = 0;
    if(IS_STATUS_(block, FREE)){
        totalDataSize = block->next - sizeof(struct Header);
        while(1){
            nblock = NEXT_BLOCK_OF_(block);
            if(IS_STATUS_(nblock, FREE) && (block->next + nblock->next) <= 16384){ // our size limit   
                block->next = block->next + nblock->next;
                totalDataSize = block->next - sizeof(struct Header);
            }else{
                break;
            }
        }
    }
    return totalDataSize;
}

void setPtrOfTempToNULL(struct Header *block){
    unsigned char *ptrAddr;
    unsigned char **accAddr;
    ptrAddr = (unsigned char *)NEXT_BLOCK_OF_(block) - sizeof(unsigned char *);
    //printf("adrress of next block : 0x%lx \n", *ptrAddr);
    //tydebug_printmem((unsigned char *)block, block->next);
    memcpy(accAddr, ptrAddr, sizeof(unsigned char *));
    //printf("addd : 0x%lx \n", (unsigned long)*accAddr);
    *((unsigned char**)*accAddr) = (unsigned char *)NULL;
}

void *tyheap_alloc( size_t size ){
    struct Header* block;
    unsigned short status = FAIL;

    status = findAvailableBlockBiggerThan((struct Header*)MEMBLOCK, &block, size);

    if(status == SUCCESS){
        status = splitBlock(block, size, OFFSET_SPLIT_SIZE);
        block->status = BUSY;
        return (void *)DATA_ADDR_OF_(block);
    }else{ // fail
        status = expandNormalSeg(block, size);
        if(status == SUCCESS){
            block->status = BUSY;
            return (void *)DATA_ADDR_OF_(block);
        }else{ // fail 
            return NULL;
        }
    }
}

void *tyheap_flash_alloc( size_t size ){
    struct Header* block;
    unsigned short status = FAIL;

    status = findAvailableBlockBiggerThan((struct Header*)START_FLASH_SEG, &block, size);
    
    if(status == SUCCESS){
        status = splitBlock(block, size, OFFSET_SPLIT_SIZE);
        block->status = BUSY;
        return (void *)DATA_ADDR_OF_(block);
    }else{
        status = expandFlashSeg(&block, size);
        if(status == SUCCESS){
            block->status = BUSY;
            return (void *)DATA_ADDR_OF_(block);
        }else{ // fail 
            return NULL;
        }
    }
}

//structure [HEADER][DATA][ADDR]
void *tyheap_tmp_alloc(size_t size, unsigned char ** ptrAddr){
    struct Header* block;
    unsigned short status = FAIL;
    unsigned short dataSize = size + sizeof(unsigned char *); 

    status = findAvailableBlockBiggerThan((struct Header*)MEMBLOCK, &block, dataSize);

    if(status == SUCCESS){
        status = splitBlock(block, dataSize, OFFSET_SPLIT_SIZE);
        block->status = TEMP;
        memcpy((unsigned char *)block + sizeof(struct Header) + size, &ptrAddr, sizeof(unsigned char *));
        return (void *)DATA_ADDR_OF_(block);
    }else{ // fail
        status = expandNormalSeg(block, dataSize);
        if(status == SUCCESS){
            block->status = TEMP;
            memcpy((unsigned char *)block + sizeof(struct Header) + size, &ptrAddr, sizeof(unsigned char *));
            return (void *)DATA_ADDR_OF_(block);
        }else{ // fail 
            return NULL;
        }
    }
}

void tyheap_free( void *ptr ){
    struct Header *block = BLOCK_OF_DATA_ADDR_(ptr);
    //we dont use switch because it may have problem with switch statment in Protothreads
    if(IS_STATUS_(block, BUSY)){
        block->status = FREE;
    }else if(IS_STATUS_(block, TEMP)){
        setPtrOfTempToNULL(block);
        block->status = FREE;
    }
    combineFreeBlock(block);
}

void  tyheap_organize(void ){
}
#if DEBUG

void tyheap_printmem(unsigned int size) {
    unsigned int i = 0;
    unsigned int address = (unsigned long)(MEMBLOCK);
    unsigned short mask_low;
    unsigned int mask_high;
    unsigned short count = 0;
    printf("---------------mem-----------------\n");
    printf("start : 0x%x\n", address);
    printf(" \t|");
    for(i = 0; i < 16; i++){
        printf("\033[0;33m");
        printf(" -%x- ",i);
        printf("\033[0m");
        if(i % 16 == 15){
            printf("\t|\n");
        }else{
            printf("\t| ");
        }
    } 

    mask_low = address & 0x0f;
    mask_high = (address >> 4) & 0xfff;

    printf("\033[0;33m");
    printf("0x%x",mask_high);
    printf("\033[0m");
    printf("\t|");
    
    for(i = 0; i < 16; i++){
        if(mask_low == i){
            count = i;
            break;
        }
        if(mask_low == i + 1){
            printf("#STA");
        }
        printf("\t| ");
        count++;
    }

    
    for(i = count; i < size + count; i++){
        if(MEMBLOCK[i] != 0){
            printf("\033[1;32m");
            printf("%x",MEMBLOCK[i]);
            printf("\033[0m");
        }else{
            printf(" ");
        }

        if(i % 16 == 15){
            printf("\t|\n");
            printf("\033[0;33m");
            printf("0x%x",++mask_high);
            printf("\033[0m");
            printf("\t|");
        }else{
            printf("\t| ");
        }
    }
    printf("#END");
    printf("\n---------------mem-----------------\n");
}

#endif