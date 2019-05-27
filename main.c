#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "process.h"
#include "queue.h"
#include "dllist.h"
#include "schedule.h"
#include "evaluate.h"


int main(int argc, char** argv){
    unsigned int numOfProc = 5, printLines=50, arrival_weight=10;
    // Error checking (invalid argc)
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes] [arrival weight] [printing lines]\n",argv[0]);
        exit(1);
    }
    if(argc >= 2){
        numOfProc = atoi(argv[1]);
    }
    if(argc >= 3){
        arrival_weight = atoi(argv[2]);
    }
    if(argc >= 4){
        printLines = atoi(argv[3]);
    }

    // Random seed
    unsigned int rnd;
    int rnd_fd = open("/dev/random", O_RDONLY);
    read(rnd_fd, &rnd, sizeof(unsigned int));
    srand(rnd);
    close(rnd_fd);

    // Initializing variables
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
        procList[i].arrival += rand() % (numOfProc * arrival_weight);

        // put Process pointer into nodeList
        nodeList[i].value = &procList[i];

    }

//    procList[0].arrival=0;
//    procList[0].cpu_burst=10;
//
//    procList[1].arrival=2;
//    procList[1].cpu_burst=3;

    printProc(procList,numOfProc);

    // Do Scheduling

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    do_FCFS(numOfProc, jobs, &chart);

    printf("FCFS scheduling start!\n");
    drawChart(&chart, printLines);
    printEvaluation(numOfProc, procList, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Non-Preemptive Shortest job first scheduling start!\n");
    do_nonpreemptive_SFJ(numOfProc, jobs, &chart);

    drawChart(&chart, printLines);
    printEvaluation(numOfProc, procList, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Preemptive Shortest job first scheduling start!\n");
    do_preemptive_SFJ(numOfProc, jobs, &chart);

    drawChart(&chart, printLines);
    printEvaluation(numOfProc, procList, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Non-Preemptive Higher priority job first scheduling start!\n");
    do_nonpreemptive_priority(numOfProc, jobs, &chart);

    drawChart(&chart, printLines);
    printEvaluation(numOfProc, procList, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<numOfProc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&procList[i]);
        push_back(jobs, &nodeList[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Preemptive Higher priority job first scheduling start!\n");
    do_preemptive_priority(numOfProc, jobs, &chart);

    drawChart(&chart, printLines);
    printEvaluation(numOfProc, procList, &chart);


    // Freeing dynamic allocated variables
    free(procList);
    free(nodeList);

    return 0;
}