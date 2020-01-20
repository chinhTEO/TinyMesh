#ifndef UC_H_
#define UC_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "ipv6.h"

void uc_send(IPV6_ADDR *address, uint8_t *data, unsigned len);

unsigned short uc_callback(uint8_t *data, unsigned short len);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //IBC_H_