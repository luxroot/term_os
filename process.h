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


typedef Process *procPtr;

void process_init(procPtr, uint);
void process_clean(procPtr);

#endif //TERM_PROCESS_H