#ifndef IBC_H_
#define IBC_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void ibc_send(uint8_t *data, unsigned len);

unsigned short ibc_callback(uint8_t *data, unsigned short len);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //IBC_H_