#ifndef UTEST_FIXED_H_
#define UTEST_FIXED_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define utest_fixed_message_length 6

unsigned short utest_fixed_callback(uint8_t *data, unsigned short len);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif