#include "tyheap.h"

//structure [status][nextindex][data  ] 
//          [ 2bit ][ 14 bit  ][ nbit ]

struct header{
    unsigned char status : 2;
    unsigned short nextIndex : 14;
};

unsigned char MEMBLOCK[SIZE_OF_HEAP];

void  tyheap_init( void ){
    //[firstblock][secondblock][data]
    // nextindex == 0 // last memory
    struct header* firstBlock = (struct header*)MEMBLOCK;
    struct header* secondBlock;
    firstBlock->status = 1;             //mark first block as busy
    firstBlock->nextIndex = 2;          //index to next block

    secondBlock = (struct header*)&MEMBLOCK[firstBlock->nextIndex];
    secondBlock->status = 0;
    secondBlock->nextIndex = 0; //i dont have next block, i am free
}

void *tyheap_malloc( size_t size ){

    return NULL;
}

void  tyheap_free( void *ptr ){

}

void  tyheap_organize(void ){

}


#ifdef UTEST

unsigned char *tyheap_MEMBLOCK(void){
    return MEMBLOCK;
}

unsigned int tyheap_sizeOfHeader(void){
    return sizeof(struct header);
}

#endif