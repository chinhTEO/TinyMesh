#ifndef MESSAGE_H_
#define MESSAGE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

enum MESSAGE_PRIOITY {
    LOW_PRIORITY,
    HIGH_PRIORITY
};

enum MESSAGE_LENGTH_TYPE{
    FIXED,
    VARIABLE
};

struct Message_out{
    unsigned short length;
    enum MESSAGE_PRIOITY priority;
    uint8_t *data;
};

unsigned short processMessageList(uint8_t *data, unsigned short len);

#if UTEST

unsigned short message_process(uint8_t *data);
enum MESSAGE_LENGTH_TYPE getTypeOfMessage(uint8_t *data);

#endif

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //MESSAGE_H_