#include <stdlib.h>
#include <stdio.h>

#include "process.h"

void process_clean(ProcPtr pc_ptr){
    pc_ptr->bursted=0;
    pc_ptr->done_time=0;
    pc_ptr->quantum=0;
    pc_ptr->waiting_time=0;
}

void process_init(ProcPtr pc_ptr, uint pid){
    pc_ptr->pid = pid;
    pc_ptr->cpu_burst = rand()  % 0x10 + 1;
    pc_ptr->io_burst = rand()   % 0x10;
    pc_ptr->arrival = rand()    % 0x10;
    pc_ptr->priority = rand()   % 0x20;
    process_clean(pc_ptr);
}

void printProc(ProcPtr procList, int n){
    int i;
    for(i=0;i<n;i++){
        printf("pid : %-3d, arrival : %-4d, cpu_burst : %-3d, priority : %-3d\n", procList[i].pid, procList[i].arrival, procList[i].cpu_burst, procList[i].priority);
    }
    puts("");
}

void printProcAfter(ProcPtr procList, int n){
    int i;
    for(i=0;i<n;i++){
        printf("pid : %d, waiting time : %d, done time : %d\n", procList[i].pid, procList[i].waiting_time, procList[i].done_time);
    }
    puts("");
}