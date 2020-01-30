#include "process.h"
#include <stdio.h>

struct process *processList;

unsigned short process_run(){
    struct process *thisProcess = processList;
    for(thisProcess = processList; thisProcess != NULL; thisProcess = thisProcess->next){
        if(thisProcess->state == PRCESS_RUNNING){
            thisProcess->state = thisProcess->thread(&thisProcess->pt);
        }   
    }
}

//unsigned short process_add(char *name, PT_THREAD((* thread)(struct pt *)))
unsigned short process_add(struct process *thisProcess){
    struct process *thisProcess = processList;
    if(processList == NULL){
        processList = thisProcess;
    }else{
        while(thisProcess->next != NULL){
            thisProcess = thisProcess->next;
        }
        thisProcess->next = thisProcess;
    }
    PT_INIT(&(thisProcess->pt));
}