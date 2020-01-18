#include "frame_header.h"

const struct HeaderField headerField[NUMBER_OF_HEADER_FIELD] = {
    8, //SELF_ADDRESS_IPV6
    2, //SELF_ADDRESS_SHORT
    2, //PAN_ID
    2, //FRAME_ID
};

unsigned short lengthOfHeader(int16_t headerList){
    unsigned short pos = 0;
    unsigned short len = 0;
    while(pos < 16){
        if(headerList < 0){
            len = len + headerField[pos].lenght;
        }
        headerList = headerList << 1;
        pos = pos + 1;
    }
    return len;
}

