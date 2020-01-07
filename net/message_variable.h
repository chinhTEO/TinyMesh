#ifndef MESSAGE_VARIABLE_H_
#define MESSAGE_VARIABLE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "message_define.h"

uint8_t *message_variable_create(enum MESSAGE_FIXED type, unsigned short *data, unsigned short length, unsigned short delay);

uint8_t message_variable_proccess(uint8_t *data);
#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_VARIABLE_H_