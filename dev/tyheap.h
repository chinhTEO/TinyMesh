#ifndef TYHEAP_H_
#define TYHEAP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define DEBUG 1
#ifndef UTEST
#define UTEST 1
#endif

#ifdef UTEST
    //#define SIZE_OF_HEAP 100
    #define SIZE_OF_HEAP 2000
#else 
    #define SIZE_OF_HEAP 300
#endif

void  tyheap_init( void );
void *tyheap_alloc( size_t size );
void *tyheap_flash_alloc( size_t size );
void *tyheap_tmp_alloc(size_t size, unsigned char ** ptrAddr);
void  tyheap_free( void *ptr );

void  tyheap_organize( void );

#if DEBUG

void tyheap_printmem(unsigned int size);
void tyheap_printblock();

#endif

#if UTEST

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


struct Header{
    unsigned char status : 2;
    uint16_t next: 14;
};

#define DATA_SIZE_OF_(ptr)              (((struct Header*)ptr)->next - sizeof(struct Header))
#define DATA_ADDR_OF_(ptr)              ((unsigned char *)ptr + sizeof(struct Header))
#define IS_STATUS_(block, _status)      (((struct Header*)block)->status == _status)
#define NEXT_BLOCK_OF_(ptr)             (struct Header*)((unsigned char *)ptr + ((struct Header*)ptr)->next)
#define SIZE_OF_(block)                 (block->next)   
#define END_BLOCK_ADDRESS()             (MEMBLOCK + SIZE_OF_HEAP)
#define BLOCK_OF_DATA_ADDR_(ptr)        (struct Header*)((unsigned char*)ptr - sizeof(struct Header))
#define IS_START_FLASH_SEG_THIS_(block) ((unsigned char *)block == START_FLASH_SEG)
#define IS_BEFORE_END_BLOCK_THIS_(block) ((unsigned char *)block + ((struct Header*)block)->next + 1 == END_NORMAL_SEG)

#define NUM_OF_FREE_BLOCK_CACHE     5
#define OFFSET_SPLIT_SIZE           5

//------------------------ expose end --------------------------//

unsigned char *tyheap_MEMBLOCK(void);
unsigned int tyheap_sizeOfHeader(void);
unsigned int tyheap_sizeOfHeap(void);

unsigned short splitBlock(struct Header *block, size_t dataSize, unsigned short offset);
unsigned short expandNormalSeg(struct Header *endBlock, size_t dataSize);
unsigned short expandFlashSeg(struct Header **startBlock, size_t dataSize);
unsigned short findAvailableBlockBiggerThan(struct Header *startBlock, struct Header **returnBlock, size_t size);
unsigned short combineFreeBlock(struct Header *startBlock);
void setPtrOfTempToNULL(struct Header *block);
void clearAllTempMemory();

extern unsigned char MEMBLOCK[SIZE_OF_HEAP];
extern unsigned char *START_FLASH_SEG; 
extern unsigned char *END_NORMAL_SEG;
#endif

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TYHEAP_H_