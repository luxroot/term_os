#include <stdlib.h>
#include "process.h"

void process_clean(procPtr pc_ptr){
    pc_ptr->bursted=0;
    pc_ptr->done_time=0;
    pc_ptr->quantum=0;
    pc_ptr->waiting_time=0;
}

void process_init(procPtr pc_ptr, uint pid){
    pc_ptr->pid=pid;
    pc_ptr->cpu_burst=rand()%10;
    pc_ptr->io_burst=rand()%10;
    pc_ptr->arrival=0;
    pc_ptr->priority=0;
    process_clean(pc_ptr);
}
