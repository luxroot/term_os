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

void print_process_info(ProcPtr proc_list, int n){
    int i;
    for(i=0;i<n;i++){
        printf("pid : %-3d| arrival : %-4d| cpu_burst : %-3d| priority : %-3d\n", proc_list[i].pid, proc_list[i].arrival, proc_list[i].cpu_burst, proc_list[i].priority);
    }
    puts("");
}

void print_process_info_changing_vars(ProcPtr proc_list, int n){
    int i;
    for(i=0;i<n;i++){
        printf("pid : %d, waiting time : %d, done time : %d\n", proc_list[i].pid, proc_list[i].waiting_time, proc_list[i].done_time);
    }
    puts("");
}