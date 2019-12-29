#ifndef TYHEAP_H_
#define TYHEAP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define DEBUG 1
#define SIZE_OF_HEAP 300

void  tyheap_init( void );
void *tyheap_alloc( size_t size );
void  tyheap_free( void *ptr );

void  tyheap_organize(void );

#if DEBUG

void tyheap_printmem(unsigned char size);

#endif

#ifdef UTEST

unsigned char *tyheap_MEMBLOCK(void);
unsigned int tyheap_sizeOfHeader(void);
unsigned int tyheap_sizeOfHeap(void);

#endif

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TYHEAP_H_