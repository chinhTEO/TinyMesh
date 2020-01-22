#include "array.h"
#include "stdio.h"

void array_print(char * const array[]){
    int i = 0;
    for(i = 0; array[i] != NULL; i++){
        printf("string %d : %s", i, array[i]);
    }
}