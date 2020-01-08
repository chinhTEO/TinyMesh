#include "message_fixed.h"
#include "tyheap.h"
#include "string.h"

#define SIZE_OF_FIXED_HEADER 1

struct Message_out *message_fixed_create(enum MESSAGE_FIXED type, uint8_t *data, unsigned short delay){
    struct Message_out *message_packet = (struct Message_out *)tyheap_flash_alloc(sizeof message_packet);
    uint8_t *packet_data = (uint8_t *)tyheap_flash_alloc(message_fixed_list[type].length + SIZE_OF_FIXED_HEADER);

    if(message_packet == NULL || packet_data == NULL){
        return NULL;
    }

    packet_data[0] = type << 1 | FIXED;
    memcpy(&packet_data[1], data, message_fixed_list[type].length);

    message_packet->data = packet_data;
    message_packet->length = message_fixed_list[type].length + SIZE_OF_FIXED_HEADER;
    message_packet->delay = delay;

    return message_packet;
}

unsigned short message_fixed_proccess(uint8_t *data){
    unsigned short i = 0;
    unsigned short flag;
    uint8_t messageId = data[0] >> 1;
    flag = message_fixed_list[messageId].recv_callback(&data[1], message_fixed_list[messageId].length);

    //raise os flag about the package

    return message_fixed_list[messageId].length + SIZE_OF_FIXED_HEADER;
}