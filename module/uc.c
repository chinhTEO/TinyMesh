#include "uc.h"
#include "frame_header.h"
#include "env_variable.h"
#include "message.h"
#include "message_define.h"
#include "message_variable.h"
#include "tymesh_framer.h"
#include <string.h>
#include <stdio.h>
#include "tyheap.h"

#define IPV6_ADDRESS_SIZE 8

void uc_send(IPV6_ADDR *address, uint8_t *data, unsigned len) {
    uint8_t *thisData = tyheap_flash_alloc(IPV6_ADDRESS_SIZE + len);
    memcpy(thisData, address, IPV6_ADDRESS_SIZE);
    memcpy((uint8_t *)&thisData[IPV6_ADDRESS_SIZE], data, len);
    struct Message_out *message = message_variable_create(MESSAGE_UC, thisData, len + IPV6_ADDRESS_SIZE, HIGH_PRIORITY);
    tymesh_framer_add(message);
}

unsigned short uc_callback(uint8_t *data, unsigned short len){
    char buffer[50];
    memcpy(buffer, data, len);
    buffer[len] = '\0';
    printf("recv from %x:%x:%x:%x:%x:%x:%x:%x : %s \n", RECV_IPV6_UUID[0],RECV_IPV6_UUID[1],RECV_IPV6_UUID[2],RECV_IPV6_UUID[3],
                                                      RECV_IPV6_UUID[4],RECV_IPV6_UUID[5],RECV_IPV6_UUID[6],RECV_IPV6_UUID[7], buffer);
}