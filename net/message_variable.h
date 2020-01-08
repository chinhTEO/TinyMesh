#ifndef MESSAGE_VARIABLE_H_
#define MESSAGE_VARIABLE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "message_define.h"

struct Message_out *message_variable_create(enum MESSAGE_VARIABLE type, uint8_t *data, unsigned short length, enum MESSAGE_PRIOITY prioity);

unsigned short message_variable_proccess(uint8_t *data);
#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_VARIABLE_H_