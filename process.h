
typedef unsigned int uint;

typedef struct _Process{
    uint pid;
    uint cpu_burst;
    uint io_burst;
    uint arrival;
    uint priority;
} Process;

typedef struct _PContainer{
    Process* proc;
    uint waiting_time;
    uint done_time;
    uint bursted;
    uint quantum;
} PContainer;

void pContainer_init(PContainer* pc_ptr);
