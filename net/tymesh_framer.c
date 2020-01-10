#include "tymesh_framer.h"
#include "message.h"
#include "queue.h"
#include <stdbool.h>
#include "tyheap.h"
#include <string.h>

struct Queue lowPriorityMessageList;
struct Queue highPriorityMessageList;

void tymesh_framer_init(){
    queue_init(&lowPriorityMessageList, NUM_OF_LOW_PRIORITY_MES_BUFFER);
    queue_init(&highPriorityMessageList, NUM_OF_HIGH_PRIORITY_MES_BUFFER);
}

void tymesh_framer_add(struct Message_out *message){
    if(message->priority == HIGH_PRIORITY){
        queue_push(&highPriorityMessageList, message);
    }else{
        queue_push(&lowPriorityMessageList, message);
    }
}

uint8_t *tymesh_framer_create(){
    unsigned short size = 0;
    struct Message_out *message;
    uint8_t *outputFrame = tyheap_alloc(LIMIT_SIZE_OF_OUTPUT_FRAME);

    while(queue_size(&highPriorityMessageList) != 0){
        message = (struct Message_out *)queue_frond(&highPriorityMessageList);
        if(message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
            memcpy(&outputFrame[size], message->data, message->length); 
            queue_pop(&highPriorityMessageList);
            size = size + message->length;
            tyheap_free(message->data);
            tyheap_free(message);
        }else{
            break;
        }
    }

    while(queue_size(&lowPriorityMessageList) != 0){
        message = (struct Message_out *)queue_frond(&lowPriorityMessageList);
        if(message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
            memcpy(&outputFrame[size], message->data, message->length); 
            queue_pop(&lowPriorityMessageList);
            size = size + message->length;
            tyheap_free(message->data);
            tyheap_free(message);
        }else{
            break;
        }
    }

    return outputFrame;
}
