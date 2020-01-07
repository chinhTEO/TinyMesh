#ifndef MESSAGE_FIXED_H_
#define MESSAGE_FIXED_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "message_define.h"

struct Message_out *message_fixed_create(enum MESSAGE_FIXED type, uint8_t *data, unsigned short delay);

unsigned short message_fixed_proccess(uint8_t *data);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_FIXED_H_