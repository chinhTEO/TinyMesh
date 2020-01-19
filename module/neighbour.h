#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

struct AdvMessage {
    uint8_t level;
};

unsigned short neighbor_adv_callback(uint8_t *data, unsigned short len);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //NEIGHBOR_H_