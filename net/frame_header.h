#ifndef FRAME_HEADER_H_
#define FRAME_HEADER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define NUMBER_OF_HEADER_FIELD 16

enum HEADER_FIELD_LIST {
    HEADER_SELF_ADDRESS_IPV6   = 0b1000000000000000,
    HEADER_SELF_ADDRESS_SHORT  = 0b0100000000000000,
    HEADER_PAN_ID              = 0b0010000000000000,
    HEADER_FRAME_ID            = 0b0001000000000000,  
};

struct HeaderField {
    unsigned short lenght;
    uint8_t *data;
};

unsigned short lengthOfHeader(int16_t headerSignature);
unsigned short createHeader(int16_t headerSignature, uint8_t *out);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TRANSFER_H_