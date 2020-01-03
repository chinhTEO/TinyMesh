#include "tydebug.h"
#include <stdio.h>

void tydebug_printmem(unsigned char *addr, unsigned short size){
    unsigned int i = 0;
    unsigned long address = (unsigned long)(addr);
    unsigned long mask_low;
    unsigned long mask_high;
    unsigned int count = 0;
    
    printf("---------------mem-----------------\n");
    printf("start : 0x%lx\n", address);
    printf(" \t|");
    for(i = 0; i < 16; i++){
        printf("\033[0;33m");
        printf(" -%x- ",i);
        printf("\033[0m");
        if(i % 16 == 15){
            printf("\t|\n");
        }else{
            printf("\t| ");
        }
    } 

    mask_low = address & 0x0f;
    mask_high = (address >> 4) & 0xfff;

    printf("\033[0;33m");
    printf("0x%lx",mask_high);
    printf("\033[0m");
    printf("\t|");
    
    for(i = 0; i < 16; i++){
        if(mask_low == i){
            count = i;
            break;
        }
        if(mask_low == i + 1){
            printf("#STA");
        }
        printf("\t| ");
        count++;
    }

    
    for(i = count; i < size + count; i++){
        if(addr[i] != 0){
            printf("\033[1;32m");
            printf("%x",addr[i]);
            printf("\033[0m");
        }else{
            printf(" ");
        }

        if(i % 16 == 15){
            printf("\t|\n");
            printf("\033[0;33m");
            printf("0x%lx",++mask_high);
            printf("\033[0m");
            printf("\t|");
        }else{
            printf("\t| ");
        }
    }
    printf("#END");
    printf("\n---------------mem-----------------\n");
}