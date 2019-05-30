#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluate.h"

void print_evaluation(uint num_of_proc, ProcPtr proc_list, ChartPtr chart_ptr){
    unsigned long long total_turnaround_time=0, total_waiting_time=0, total_response_time=0;
    unsigned int i=0, last_timeline, working_time=0, context_switches=0;
    double average_turnaround_time=0, average_waiting_time=0, throughput=0, cpu_utilization=0, average_response_time=0;
    unsigned int* first_response_time = (unsigned int*)malloc(sizeof(unsigned int) * num_of_proc);
    memset(first_response_time, 0, sizeof(unsigned int) * num_of_proc);

    while(1){
        if(chart_ptr->processes[i] == 0)
            break;
        if(chart_ptr->end[i] == chart_ptr->start[i+1])
            context_switches++;
        if(!first_response_time[chart_ptr->processes[i]-1])
            first_response_time[chart_ptr->processes[i]-1] = chart_ptr->end[i];
        working_time += chart_ptr->end[i] - chart_ptr->start[i];
        i++;
    }
    last_timeline = chart_ptr->end[i-1];
    throughput = (double) num_of_proc / last_timeline;
    cpu_utilization = (double) working_time / last_timeline * 100;

    for(i=0;i<num_of_proc; i++){
        total_response_time += first_response_time[i] - proc_list[i].arrival;
    }
    average_response_time = (double) total_response_time / num_of_proc;

    for(i=0;i<num_of_proc; i++){
        total_turnaround_time += proc_list[i].done_time - proc_list[i].arrival;
        total_waiting_time += proc_list[i].waiting_time;
    }
    average_turnaround_time = (double) total_turnaround_time / num_of_proc;
    average_waiting_time = (double) total_waiting_time / num_of_proc;

    printf("Throughput : %lf [processes per unit time] / CPU Utilization : %lf%%\n", throughput, cpu_utilization);
    printf("Total / Average Turnaround Time : %lld / %lf\n", total_turnaround_time, average_turnaround_time);
    printf("Total / Average Waiting Time : %lld / %lf\n", total_waiting_time, average_waiting_time);
    printf("Total / Average Response Time : %lld / %lf\n", total_response_time, average_response_time);
    printf("Context Switches / Percentage to Waiting Time : %d / %lf%%\n", context_switches,
            (double)context_switches/(context_switches+10*total_waiting_time)*100);
    printf("(Assumed that context switching has cost of 0.1\n\n");

    // free dynamically allocated variables
    free(first_response_time);
}