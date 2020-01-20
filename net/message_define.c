#include "message_define.h"
#include <string.h>
#include "frame_header.h"
#include "abc.h"
#include "ibc.h"
#include "uc.h"

#if UTEST
#include "utest_fixed.h"
#include "utest_variable.h"
#endif

const struct Message_variable_define message_variable_list[NUMBER_OF_MESSAGE_VARIABLE] = {
#if UTEST
    {0 , utest_variable_callback},
#endif
    {0 , abc_callback},
    {HEADER_SELF_ADDRESS_IPV6, ibc_callback},
    {HEADER_SELF_ADDRESS_IPV6, uc_callback},
};

const struct Message_fixed_define message_fixed_list[NUMBER_OF_MESSAGE_FIXED] = {
#if UTEST
    {3, utest_fixed_message_length , utest_fixed_callback},
#endif
};