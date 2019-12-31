#include "tyheap.h"
#include <string.h>

#if !UTEST
#include <stdint.h>
#include <string.h>

#if DEBUG
    #include <stdio.h>
#endif


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

    block = &MEMBLOCK[SIZE_OF_HEAP - sizeof(struct Header)];
    block->status = END;
    block->next = 0;

    START_FLASH_SEG = (unsigned char*)block;
}

struct Header* findAvailableBlockBiggerThan(size_t size){
    struct Header* block = (struct Header*)MEMBLOCK;
    struct Header* addr = NULL;
    while(1){
        if(IS_STATUS_(block,FREE)){
            if(DATA_SIZE_OF_(block) >= size){
                addr = (struct Header* )DATA_ADDR_OF_(block);
                break;
            }
        }

        if(IS_STATUS_(block, END)){
            addr = (struct Header* )DATA_ADDR_OF_(block);
            break;
        }
        else
            block = NEXT_BLOCK_OF_(block);
    }
    return addr;
}

unsigned short createNewBLockBeginAt(struct Header *block, size_t dataSize){
    //[HEADER][DATA SIZE][HEADER END]
    if((unsigned char *)block + dataSize + sizeof(struct Header)*2 < END_BLOCK_ADDRESS()){
        block->status = FREE;
        block->next   = sizeof(struct Header) + dataSize;

        block = NEXT_BLOCK_OF_(block);
        block->status = END; 
    
        return SUCCESS;
    }else{
        return FAIL;
    }
}

unsigned short splitBlock(struct Header *block, size_t dataSize, unsigned short offset){
    struct Header *nblock;
    
    if(DATA_SIZE_OF_(block) >= sizeof(struct Header) + dataSize + offset) {
        nblock = (unsigned char *)block + dataSize + sizeof(struct Header);

        nblock->next = SIZE_OF_(block) - sizeof(struct Header) - dataSize;
        nblock->status = FREE;

        block->next = sizeof(struct Header) + dataSize;
        return SUCCESS;
    }else{
        return FAIL;
    }
}

void *tyheap_alloc( size_t size ){
    struct Header* block = (struct Header*)MEMBLOCK;
    unsigned short status = FAIL;

    if(IS_STATUS_(block, FREE)){
        //SPLIT
        status = splitBlock(block, size, OFFSET_SPLIT_SIZE);
        return (void *)DATA_ADDR_OF_(block);
        
    }else if(IS_STATUS_(block, END)){
        status = createNewBLockBeginAt(block, size);
        if(status == SUCCESS){
            return (void *)DATA_ADDR_OF_(block);
        }else{
            return NULL;
        }
    }
}

void  tyheap_free( void *ptr ){
}

void  tyheap_organize(void ){
}
#if DEBUG

void tyheap_printmem(unsigned int size) {
    unsigned int i = 0;
    unsigned int address = (unsigned long)(MEMBLOCK);
    unsigned short mask_low;
    unsigned short mask_high;
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
    mask_high = (address >> 4) & 0x0f;

    printf("\033[0;33m");
    printf("0x%x",mask_high);
    printf("\033[0m");
    printf("\t|");
    
    for(i = 0; i < 16; i++){
        if(mask_low == i){
            count = i;
            break;
        }
        printf("  ");
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

#if UTEST

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