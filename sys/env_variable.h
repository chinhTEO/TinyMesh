#ifndef ENV_VARIABLE_H_
#define ENV_VARIABLE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

extern uint8_t IPV6_UUID[8];
extern uint8_t SHORT_UUID[2];
extern uint8_t PAN_ID[2];
extern uint8_t BATTERY_PERCENTAGE;
extern uint8_t BARRIER_LEVEL;


#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TRANSFER_H_