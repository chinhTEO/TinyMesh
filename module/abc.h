#ifndef ABC_H_
#define ABC_H_
#include <stdint.h>

void abc_send(uint8_t *data, unsigned len);

unsigned short abc_callback(uint8_t *data, unsigned short len);

#endif