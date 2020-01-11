#include "message_variable.h"
#include "string.h"
#include "tyheap.h"

#define SIZE_OF_VARIABLE_HEADER 2
#define TYPE_INFO_POS 0
#define LENGH_INFO_POS 1
#define DATA_POS 2

struct Message_out *message_variable_create(enum MESSAGE_VARIABLE type, uint8_t *data, unsigned short length, enum MESSAGE_PRIOITY priority){
    struct Message_out *message_packet = (struct Message_out *)tyheap_flash_alloc(sizeof(struct Message_out));
    uint8_t *packet_data = (uint8_t *)tyheap_flash_alloc(length + SIZE_OF_VARIABLE_HEADER);

    if(message_packet == NULL || packet_data == NULL){
        return NULL;
    }

    packet_data[TYPE_INFO_POS] = type << 1 | VARIABLE;
    packet_data[LENGH_INFO_POS] = length;

    memcpy(&packet_data[DATA_POS], data, length);

    message_packet->length = length + SIZE_OF_VARIABLE_HEADER;
    message_packet->priority = priority;
    message_packet->data = packet_data;

    return message_packet;
}

unsigned short message_variable_proccess(uint8_t *data){
    uint8_t len = data[LENGH_INFO_POS];
    unsigned short even = message_variable_list[data[TYPE_INFO_POS] >> 1].recv_callback(&data[TYPE_INFO_POS], len);
    // dosome thing noti for example
    return len + SIZE_OF_VARIABLE_HEADER; // 2 byte for header + len data byte = num of byte is processed
}