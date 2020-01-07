#ifndef MESSAGE_H_
#define MESSAGE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

enum MESSAGE_LENGTH_TYPE{
    FIXED,
    VARIABLE
};

struct Message_out{
    unsigned short length;
    unsigned short delay;
    uint8_t *data;
};

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_H_