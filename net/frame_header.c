#include "frame_header.h"
#include "env_variable.h"
#include "string.h"

IPV6_ADDR RECV_IPV6_UUID;
uint8_t RECV_SHORT_UUID[2];
uint8_t RECV_PAN_ID[2];
uint8_t RECV_BATTERY_PERCENTAGE;
uint8_t RECV_BARRIER_LEVEL;
uint16_t RECV_FRAME_NUMBER;

const struct HeaderField headerField[NUMBER_OF_HEADER_FIELD] = {
    {8, (uint8_t *)&IPV6_UUID, (uint8_t *)&RECV_IPV6_UUID},                                   //SELF_ADDRESS_IPV6
    {2, SHORT_UUID, RECV_SHORT_UUID},                                 //SELF_ADDRESS_SHORT
    {2, PAN_ID , RECV_PAN_ID},                                        //PAN_ID
    {2, (uint8_t *)&FRAME_NUMBER, (uint8_t *)&RECV_FRAME_NUMBER}      //FRAME_ID
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

unsigned short proccessHeader(uint8_t *header){
    unsigned short pos = 0;
    unsigned short len = 2;  // 2 byte for signature
    int16_t headerSignature = *((int16_t *)header);
    while(pos < 16){
        if(headerSignature < 0){
            memcpy(headerField[pos].recv_data, &header[len], headerField[pos].lenght); 
            len = len + headerField[pos].lenght;
        }
        headerSignature = headerSignature << 1;
        pos = pos + 1;
    }
    return len;
}
