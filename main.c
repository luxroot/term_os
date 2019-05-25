#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "process.h"
#include "queue.h"
#include "dllist.h"
#include "schedule.h"

void printProc(ProcPtr procList, int n){
    int i;
    for(i=0;i<n;i++){
        printf("pid : %d, arrival : %d, burst : %d\n", procList[i].pid, procList[i].arrival, procList[i].cpu_burst);
    }
}

int main(int argc, char** argv){
    // Error checking (invalid argc)
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes]\n",argv[0]);
        exit(1);
    }

    // Random seed
    unsigned int rnd;
    int rnd_fd = open("/dev/random", O_RDONLY);
    read(rnd_fd, &rnd, sizeof(unsigned int));
    srand(rnd);
    close(rnd_fd);

    // Initializing variables
    unsigned int numOfProc = atoi(argv[1]);
    unsigned int i;

    DLList _jobs;
    DLLptr jobs = &_jobs;
    DLList_init(jobs);

    Chart chart={0};

    // Contains real process
    ProcPtr procList = (ProcPtr) malloc(sizeof(Process) * numOfProc);
    // Contains real node which has process pointer inside
    NodePtr nodeList = (NodePtr) malloc(sizeof(Node) * numOfProc);

    for(i=0;i<numOfProc;i++){
        // initialize with random variable, and pid of i (these variables must be constant after init)
        process_init(&procList[i], i+1);
        procList[i].arrival += rand() % (numOfProc * 15);

        // put Process pointer into nodeList
        nodeList[i].value = &procList[i];

        push_back(jobs, &nodeList[i]);
    }
    printProc(procList,numOfProc);

    // Do Scheduling

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    do_FCFS(numOfProc, jobs, &chart);

    i=0;
    while(1){
        if(chart.processes[i] == 0){
            break;
        }
        printf("Timeline : %d ~ %d pid : %d\n", chart.start[i], chart.end[i], chart.processes[i]);
        i++;
    }
    drawChart(&chart, numOfProc, 50);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    do_nonpreemptive_SFJ(numOfProc, jobs, &chart);

    i=0;
    while(1){
        if(chart.processes[i] == 0){
            break;
        }
        printf("Timeline : %d ~ %d pid : %d\n", chart.start[i], chart.end[i], chart.processes[i]);
        i++;
    }
    drawChart(&chart, numOfProc, 50);


    // Freeing dynamic allocated variables
    free(procList);
    free(nodeList);

    return 0;
}