#include "message_define.h"
#include <string.h>

struct Message_variable_define message_variable_list[NUMBER_OF_MESSAGE_VARIABLE] = {
#if UTEST
    NULL,
#endif
};

struct Message_fixed_define message_fixed_list[NUMBER_OF_MESSAGE_FIXED] = {
#if UTEST
    { 6 , NULL},
#endif
};