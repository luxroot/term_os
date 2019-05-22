#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "process.h"
#include "queue.h"
#include "dllist.h"


int main(int argc, char** argv){
    // Error checking (invalid argc)
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes]\n",argv[0]);
        exit(1);
    }

    // Random seed
    int rnd;
    int rnd_fd = open("/dev/random", O_RDONLY);
    read(rnd_fd, &rnd, sizeof(int));
    srand(rnd);
    close(rnd_fd);

    // Initializing variables
    unsigned int numOfProc = atoi(argv[1]);
    unsigned int i;

    DLList _jobs;
    DLLptr jobs = &_jobs;
    DLList_init(jobs);

    // Contains real process
    ProcPtr procList = (ProcPtr) malloc(sizeof(Process) * numOfProc);
    // Contains real node which has process pointer inside
    NodePtr nodeList = (NodePtr) malloc(sizeof(Node) * numOfProc);

    for(i=0;i<numOfProc;i++){
        // initialize with random variable, and pid of i (these variables must be constant after init)
        process_init(&procList[i], i+1);

        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);

        // put Process pointer into nodeList
        nodeList[i].value = &procList[i];
    }

    // Do Scheduling



    // Freeing dynamic allocated variables
    free(procList);
    free(nodeList);

    return 0;
}