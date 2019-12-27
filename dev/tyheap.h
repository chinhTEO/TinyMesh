#ifndef TYHEAP_H_
#define TYHEAP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void  tyheap_init( void );
void *tyheap_malloc( size_t size );
void  tyheap_free( void *ptr );

void  tyheap_organize(void );

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TYHEAP_H_