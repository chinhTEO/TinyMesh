#include "nb_test.h"
#include "queue.h"
#include <stdint.h>
#include "string.h"
#include <stdlib.h>

struct Queue nbt_snap_list;

void NBT_BEGIN(){
    queue_init(&nbt_snap_list, 0xffff);
}

bool conditionFunction(void *element, unsigned short pos, void *arg){
    if(strcmp((char *)arg, ((struct nbt_snap *)element)->key_UUID) == 0){
        return true;
    }else{
        return false;
    }
}

bool nbt_cmp(char *key_UUID, void *data){
    int i = 0;
    struct nbt_snap *snap = queue_find(&nbt_snap_list, conditionFunction, (void *)key_UUID);
    if(snap != NULL){
        for(i = 0; i < snap->len; i++){
            if(((uint8_t *)snap->data)[i] != ((uint8_t *)data)[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}



void NBT_END(){
    struct nbt_snap *snap;
    while(queue_size(&nbt_snap_list)){
        snap = (struct nbt_snap *)queue_frond(&nbt_snap_list);
        free(snap->key_UUID);
        free(snap->data);
        queue_pop(&nbt_snap_list);
        free(snap);
    }
}

void *NBT_GET(char *UUID){
    return queue_find(&nbt_snap_list, conditionFunction, (void *)UUID);
}

void nbt_add_snap(char *UUID, void *data, unsigned int len){
    struct nbt_snap *snap = malloc(sizeof(struct nbt_snap));
    snap->key_UUID = malloc(sizeof(char)*100);
    strcpy(snap->key_UUID, UUID);
    snap->data = malloc(len);
    memcpy(snap->data, data, len);
    queue_push((void *)&nbt_snap_list, snap);
}