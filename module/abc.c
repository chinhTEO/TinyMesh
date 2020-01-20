#include "abc.h"
#include "message_variable.h"
#include "message.h"
#include "tymesh_framer.h"
#include "string.h"
#include <stdio.h>

void abc_send(uint8_t *data, unsigned len){
    struct Message_out *message = message_variable_create(MESSAGE_ABC, data, len, HIGH_PRIORITY);
    tymesh_framer_add(message);
}

unsigned short abc_callback(uint8_t *data, unsigned short len){
    char buffer[50];
    memcpy(buffer, data, len);
    buffer[len] = '\0';
    printf("recv from abc: %s \n", buffer);
}