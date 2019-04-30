#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"

int main(int argc, char** argv){
    printf("BB");
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes]\n",argv[0]);
        exit(1);
    }
    int numOfProc=0;
    numOfProc = atoi(argv[1]);
    printf("aa : %d\n",numOfProc);

    Process pc;
    process_init(&pc, 3);

    Queue qu;
    queue_init(&qu);

    enque(&qu, &pc);

    queue_destroy(&qu);
    return 0;
}