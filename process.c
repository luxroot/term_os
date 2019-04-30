#include "process.h"

void pContainer_init(PContainer* pc_ptr){
    pc_ptr->bursted=0;
    pc_ptr->done_time=0;
    pc_ptr->quantum=0;
    pc_ptr->waiting_time=0;
}
