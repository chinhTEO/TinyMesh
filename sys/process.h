#ifndef PROCESS_H_ 
#define PROCESS_H_
#include "pt.h"

enum PROCESS_STATE {
    PRCESS_RUNNING,
    PROCESS_HALL,
    PROCESS_EXIT,
    PROCESS_WAIT
};

struct process {
    struct proccess *next;
    PT_THREAD((* thread)(struct pt *));
    struct pt pt;
    enum PROCESS_STATE state;
};

unsigned short process_run(); 
unsigned short process_add(struct process *thisProcess);

#ifdef UTEST
    extern struct proccess process_list;
#else 

#endif //PROCESS_H_