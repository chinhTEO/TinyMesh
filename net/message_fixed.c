#include "message_fixed.h"
#include "tyheap.h"
#include "string.h"

struct Message_out *message_fixed_create(enum MESSAGE_FIXED type, uint8_t *data, unsigned short delay){
    struct Message_out *message_packet = (struct Message_out *)tyheap_flash_alloc(sizeof message_packet);
    uint8_t *packet_data = (uint8_t *)tyheap_flash_alloc(message_fixed_list[type].length + 1);

    if(message_packet == NULL){
        return NULL;
    }

    packet_data[0] = type << 1 | FIXED;
    memcpy(&packet_data[1], data, message_fixed_list[type].length);

    message_packet->data = packet_data;
    message_packet->length = message_fixed_list[type].length;
    message_packet->delay = delay;

    return message_packet;
}

uint8_t message_fixed_proccess(uint8_t *data){

}