#ifndef IPV6_H_
#define IPV6_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <string.h>

typedef union IPV6_ADDR {
    uint8_t  u8[8];                      /* Initializer, must come first. */
    uint16_t u16[4];  
} IPV6_ADDR;

#define ipv6addr_cmp(addr1, addr2) (memcmp(addr1, addr2, sizeof(IPV6_ADDR)) == 0)

void ipv6_printaddress(IPV6_ADDR addr);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //IPV6_H_