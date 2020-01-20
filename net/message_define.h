#ifndef MESSAGE_DEFINE_H_
#define MESSAGE_DEFINE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "message.h"

#define NUMBER_OF_MESSAGE_VARIABLE 4
#define NUMBER_OF_MESSAGE_FIXED 2

enum MESSAGE_VARIABLE {
#if UTEST
    MESSAGE_UTEST_VARIABLE, 
#endif
    MESSAGE_ABC,
    MESSAGE_IBC,
    MESSAGE_UC,
};

enum MESSAGE_FIXED {
#if UTEST
    MESSAGE_UTEST_FIXED,
#endif
    MESSAGE_ADV,
};

struct Message_variable_define {
    uint16_t headerRequirement;
    unsigned short (*recv_callback)(uint8_t *data, unsigned short len);
};

struct Message_fixed_define {
    uint16_t headerRequirement;
    unsigned short length;
    unsigned short (*recv_callback)(uint8_t *data, unsigned short len);     
};

extern const struct Message_variable_define message_variable_list[NUMBER_OF_MESSAGE_VARIABLE];
extern const struct Message_fixed_define message_fixed_list[NUMBER_OF_MESSAGE_FIXED];

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_DEFINE_H_