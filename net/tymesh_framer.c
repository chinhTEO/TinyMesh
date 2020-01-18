#include "tymesh_framer.h"
#include "message.h"
#include "queue.h"
#include <stdbool.h>
#include "tyheap.h"
#include <string.h>

struct Queue lowPriorityMessageList;
struct Queue highPriorityMessageList;
struct Message_out *frame_header;


void tymesh_framer_init(){
    queue_init(&lowPriorityMessageList, NUM_OF_LOW_PRIORITY_MES_BUFFER);
    queue_init(&highPriorityMessageList, NUM_OF_HIGH_PRIORITY_MES_BUFFER);
    frame_header = NULL;
}

void tymesh_framer_add(struct Message_out *message){
    if(message->priority == HIGH_PRIORITY){
        queue_push(&highPriorityMessageList, message);
    }else{
        queue_push(&lowPriorityMessageList, message);
    }
}

uint8_t *tymesh_framer_create(unsigned short *len){
    unsigned short size = 0;
    struct Message_out *message;
    uint8_t *outputFrame = tyheap_flash_alloc(LIMIT_SIZE_OF_OUTPUT_FRAME);

    

    if(frame_header != NULL){
        memcpy(&outputFrame[size], frame_header->data, frame_header->length); 
        size = size + message->length;
        tyheap_free(frame_header->data);
        tyheap_free(frame_header); 
        frame_header = NULL;
    }

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

    *len = size;
    return outputFrame;
}
