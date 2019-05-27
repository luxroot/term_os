#ifndef TERM_PROCESS_H
#define TERM_PROCESS_H

typedef unsigned int uint;

typedef struct _Process{
    uint pid;
    uint cpu_burst;
    uint io_burst;
    uint arrival;
    uint priority;

    // Changing variables
    uint waiting_time;
    uint done_time;
    uint bursted;
    uint quantum;
} Process;


typedef Process *ProcPtr;

void process_init(ProcPtr, uint);
void process_clean(ProcPtr);

void print_process_info(ProcPtr procList, int n);
void print_process_info_changing_vars(ProcPtr procList, int n);

#endif //TERM_PROCESS_H