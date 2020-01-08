#include "message.h"
#include "message_fixed.h"
#include "message_variable.h"


enum MESSAGE_LENGTH_TYPE getTypeOfMessage(uint8_t *data){
    if((*data & 0x01) == VARIABLE){
        return VARIABLE;
    }else{
        return FIXED;
    }
}

unsigned short message_process(uint8_t *data){
    unsigned short len;
    if(getTypeOfMessage(data) == FIXED){
        len = message_fixed_proccess(data);
    }else{
        len = message_variable_proccess(data);
    }
    return len;

}


unsigned short processMessageList(uint8_t *data, unsigned short len){
    unsigned short pos = 0;
    unsigned short package_len = 0;
    do{
        package_len = message_process(&data[pos]);
        pos += package_len;
    }while(pos < len - 1);

    return pos;
}
