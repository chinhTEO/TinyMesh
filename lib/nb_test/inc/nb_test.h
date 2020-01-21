#ifndef NB_TEST_H_
#define NB_TEST_H_
#ifdef __cplusplus
extern "C" {
#endif

#if(NBT_UTEST_SUPPORT)

#include <string.h>
#include <stdbool.h>


#define NBT_SNAP(UUID, snap_data, len)  nbt_add_snap(#UUID, snap_data, len)
#define NBT_CMP(UUID, data) (int)nbt_cmp(#UUID, data)

void NBT_BEGIN();
void NBT_END();
bool nbt_cmp(char *key_UUID, void *data);
void nbt_add_snap(char *UUID, void *data, unsigned int len);

struct nbt_snap {
    struct nbt_snap *next;
    char *key_UUID;
    void *data;
    unsigned int len;
};

#if(BUILD_TEST) 
#include "../src/queue.h"
extern struct Queue nbt_snap_list;
#endif

#else
    #define NBT_SNAP(UUID, snap_data, len)
#endif //NBT_UTEST_SUPPORT

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif //NB_TEST_H_