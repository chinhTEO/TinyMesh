#ifndef TYMESH_FRAMER
#define TYMESH_FRAMER
#ifdef __cplusplus
extern "C" {
#endif
#include "message.h"

#define NUM_OF_LOW_PRIORITY_MES_BUFFER   4
#define NUM_OF_HIGH_PRIORITY_MES_BUFFER  4
#define LIMIT_SIZE_OF_OUTPUT_FRAME       120

void tymesh_framer_init();
void tymesh_framer_add(struct Message_out *message);
uint8_t *tymesh_framer_create();


#if UTEST

//------------------------ expose start --------------------------//
extern struct Queue lowPriorityMessageList;
extern struct Queue highPriorityMessageList;

//------------------------ expose end --------------------------//
#endif

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif