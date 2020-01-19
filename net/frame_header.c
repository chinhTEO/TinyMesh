#include "frame_header.h"
#include "env_variable.h"
#include "string.h"

const struct HeaderField headerField[NUMBER_OF_HEADER_FIELD] = {
    {8, IPV6_UUID},     //SELF_ADDRESS_IPV6
    {2, SHORT_UUID},    //SELF_ADDRESS_SHORT
    {2, PAN_ID},        //PAN_ID
    {2, (uint8_t *)&FRAME_NUMBER}  //FRAME_ID
};

unsigned short lengthOfHeader(int16_t headerSignature){
    unsigned short pos = 0;
    unsigned short len = 2;  // 2 byte for signature
    while(pos < 16){
        if(headerSignature < 0){
            len = len + headerField[pos].lenght;
        }
        headerSignature = headerSignature << 1;
        pos = pos + 1;
    }
    return len;
}

unsigned short createHeader(int16_t headerSignature, uint8_t *out){
    unsigned short pos = 0;
    unsigned short len = 2; // 2 byte for signature
    memcpy(out, (uint8_t *)&headerSignature, 2);
    while(pos < 16){
        if(headerSignature < 0){
            memcpy(&out[len], headerField[pos].data, headerField[pos].lenght); 
            len = len + headerField[pos].lenght;
        }
        headerSignature = headerSignature << 1;
        pos = pos + 1;
    }
    return len;
}

