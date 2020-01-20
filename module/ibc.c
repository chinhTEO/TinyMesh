#include "ibc.h"
#include "frame_header.h"
#include "env_variable.h"
#include "message.h"
#include "message_define.h"
#include "message_variable.h"
#include "tymesh_framer.h"
#include <string.h>
#include <stdio.h>

void ibc_send(uint8_t *data, unsigned len){
    struct Message_out *message = message_variable_create(MESSAGE_IBC, data, len, HIGH_PRIORITY);
    tymesh_framer_add(message);
}

unsigned short ibc_callback(uint8_t *data, unsigned short len){
    char buffer[50];
    memcpy(buffer, data, len);
    buffer[len] = '\0';
    printf("recv from %x:%x:%x:%x:%x:%x:%x:%x : %s \n", RECV_IPV6_UUID.u8[0],RECV_IPV6_UUID.u8[1],RECV_IPV6_UUID.u8[2],RECV_IPV6_UUID.u8[3],
                                                      RECV_IPV6_UUID.u8[4],RECV_IPV6_UUID.u8[5],RECV_IPV6_UUID.u8[6],RECV_IPV6_UUID.u8[7], buffer);
}