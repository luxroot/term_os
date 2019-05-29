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
    uint cpu_bursted;
    uint quantum;
    uint io_bursted;
    uint first_io;
} Process;


typedef Process *ProcPtr;

void process_init(ProcPtr, uint);
void process_clean(ProcPtr);

void print_process_info(ProcPtr, int);
void print_process_info_changing_vars(ProcPtr, int);

#endif //TERM_PROCESS_H