#include "tymesh_framer.h"
#include "message.h"
#include "queue.h"
#include <stdbool.h>
#include "tyheap.h"
#include <string.h>
#include "frame_header.h"

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
    struct Queue messageList;
    uint16_t headerSignature = 0;
    unsigned short headerLength = 0;
    
    //uint8_t *outputFrame = tyheap_flash_alloc(LIMIT_SIZE_OF_OUTPUT_FRAME);
    queue_init(&messageList, 100);
    

    // if(frame_header != NULL){
    //     memcpy(&outputFrame[size], frame_header->data, frame_header->length); 
    //     size = size + message->length;
    //     tyheap_free(frame_header->data);
    //     tyheap_free(frame_header); 
    //     frame_header = NULL;
    // }

    while(queue_size(&highPriorityMessageList) != 0){
        message = (struct Message_out *)queue_frond(&highPriorityMessageList);
        if(headerSignature == (headerSignature | message->headerRequirement)){
            if(headerLength + message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
                // memcpy(&outputFrame[size], message->data, message->length);
                queue_push(&messageList, message); 
                queue_pop(&highPriorityMessageList);
                size = size + message->length;
                // tyheap_free(message->data);
                // tyheap_free(message);
            }else{
                break;
            }
        }else{
            if( lengthOfHeader(headerSignature | message->headerRequirement) + message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
                headerLength = lengthOfHeader(headerSignature | message->headerRequirement);
                // memcpy(&outputFrame[size], message->data, message->length);
                queue_push(&messageList, message); 
                queue_pop(&highPriorityMessageList);
                size = size + message->length;
                // tyheap_free(message->data);
                // tyheap_free(message);
            }else{
                break;
            }
        }
    }

    while(queue_size(&lowPriorityMessageList) != 0){
        message = (struct Message_out *)queue_frond(&lowPriorityMessageList);
        if(headerSignature == (headerSignature | message->headerRequirement)){
            if(headerLength + message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
                // memcpy(&outputFrame[size], message->data, message->length);
                queue_push(&messageList, message); 
                queue_pop(&lowPriorityMessageList);
                size = size + message->length;
                // tyheap_free(message->data);
                // tyheap_free(message);
            }else{
                break;
            }
        }else{
            if( lengthOfHeader(headerSignature | message->headerRequirement) + message->length + size < LIMIT_SIZE_OF_OUTPUT_FRAME){
                headerLength = lengthOfHeader(headerSignature | message->headerRequirement);
                // memcpy(&outputFrame[size], message->data, message->length);
                queue_push(&messageList, message); 
                queue_pop(&lowPriorityMessageList);
                size = size + message->length;
                // tyheap_free(message->data);
                // tyheap_free(message);
            }else{
                break;
            }
        }
    }

    uint8_t *outputFrame = tyheap_flash_alloc(headerLength + size);
    size = 0;

    createHeader(headerSignature, outputFrame);
    size = headerLength;

    while(queue_size(&messageList) != 0){
        message = (struct Message_out *)queue_frond(&messageList);
        memcpy(&outputFrame[size], message->data, message->length);
        size = size + message->length;
        queue_pop(&messageList);
        tyheap_free(message->data);
        tyheap_free(message);
    }

    *len = size;
    return outputFrame;
}

unsigned short tymesh_framer_process(uint8_t *data, unsigned short len){
    unsigned short headerLen = proccessHeader(data);
    processMessageList(&data[headerLen], len - headerLen);
}