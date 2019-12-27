#ifndef TYHEAP_H_
#define TYHEAP_H_

#include <stddef.h>

void  tyheap_init( void );
void *tyheap_malloc( size_t size );
void  tyheap_free( void *ptr );

void  tyheap_organize(void );

#endif