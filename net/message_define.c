#include "message_define.h"
#include <string.h>
#if UTEST
#include "utest_fixed.h"
#include "utest_variable.h"
#endif

const struct Message_variable_define message_variable_list[NUMBER_OF_MESSAGE_VARIABLE] = {
#if UTEST
    utest_variable_callback,
#endif
};

const struct Message_fixed_define message_fixed_list[NUMBER_OF_MESSAGE_FIXED] = {
#if UTEST
    { utest_fixed_message_length , utest_fixed_callback},
#endif
};