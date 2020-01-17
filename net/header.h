#ifndef HEADER_H_
#define HEADER_H_
#ifdef __cplusplus
extern "C" {
#endif

enum HEADER_FIELD_LIST {
    SELF_ADDRESS_IPV6,
    SELF_ADDRESS_SHORT,
    PAN_ID,
    FRAME_ID,  
};

struct HeaderField {
    unsigned short lenght;
};


#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //TRANSFER_H_