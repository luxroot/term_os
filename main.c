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
    unsigned int num_of_proc = 5, print_lines=50, arrival_weight=10, time_quantum=3;
    // Error checking (invalid argc)
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes] [[time quantum=3]] [[arrival weight]=10] [[printing lines=50]]\n",argv[0]);
        exit(1);
    }
    if(argc >= 2){
        num_of_proc = atoi(argv[1]);
    }
    if(argc >= 3){
        time_quantum = atoi(argv[2]);
    }
    if(argc >= 4){
        arrival_weight = atoi(argv[3]);
    }
    if(argc >= 5){
        print_lines = atoi(argv[4]);
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
    ProcPtr proc_list = (ProcPtr) malloc(sizeof(Process) * num_of_proc);
    // Contains real node which has process pointer inside
    NodePtr node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);


    for(i=0;i<num_of_proc;i++){
        // initialize with random variable, and pid of i (these variables must be constant after init)
        process_init(&proc_list[i], i+1);
	if(arrival_weight)
	        proc_list[i].arrival += rand() % (num_of_proc * arrival_weight);

        // put Process pointer into node_list
        node_list[i].value = &proc_list[i];

    }

//    proc_list[0].io_burst=3;
//    proc_list[0].arrival=0;
//    proc_list[0].cpu_burst=5;
//
//    proc_list[1].io_burst=2;
//    proc_list[1].arrival=10;
//    proc_list[1].cpu_burst=3;
//
//    proc_list[2].io_burst=3;
//    proc_list[2].arrival=13;
//    proc_list[2].cpu_burst=21;


    print_process_info(proc_list, num_of_proc);

    // Do Scheduling

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    do_FCFS(num_of_proc, jobs, &chart);

    printf("FCFS scheduling start!\n");
    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);


    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Non-Preemptive Shortest job first scheduling start!\n");
    do_non_preemptive_SFJ(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);


    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Preemptive Shortest job first scheduling start!\n");
    do_preemptive_SFJ(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);


    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Non-Preemptive Higher priority job first scheduling start!\n");
    do_non_preemptive_priority(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Preemptive Higher priority job first scheduling start!\n");
    do_preemptive_priority(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Round Robin scheduling start!\n");
    do_round_robin(num_of_proc, jobs, &chart, time_quantum);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);


    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Non-Preemptive HRRN scheduling start!\n");
    do_non_preemptive_HRRN(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);

    /////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0;i<num_of_proc;i++){
        // initialize changing variables (these variables changes with scheduling algorithm)
        process_clean(&proc_list[i]);
        push_back(jobs, &node_list[i]);
    }
    memset(&chart, 0, sizeof(chart));

    printf("Preemptive HRRN scheduling start!\n");
    do_preemptive_HRRN(num_of_proc, jobs, &chart);

    drawChart(&chart, print_lines);
    print_evaluation(num_of_proc, proc_list, &chart);

    // Freeing dynamic allocated variables
    free(proc_list);
    free(node_list);

    return 0;
}
