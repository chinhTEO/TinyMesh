#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "stdint.h"

enum MESSAGE_LENGTH_TYPE{
    FIXED,
    VARIABLE
};

struct message_info {
    unsigned short length;
    enum MESSAGE_LENGTH_TYPE type;
    void (*recv_callback)(unit8_t *data, unsigned short len);
};

#endif //MESSAGE_H_