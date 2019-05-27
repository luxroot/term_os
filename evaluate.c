#include <stdio.h>

#include "evaluate.h"

void print_evaluation(uint num_of_proc, ProcPtr proc_list, ChartPtr chart_ptr){
    unsigned long long total_turnaround_time=0, total_waiting_time=0;
    unsigned int i=0, last_timeline, working_time=0;
    double average_turnaround_time=0, average_waiting_time=0, throughput=0, cpu_utilization=0;

    while(1){
        if(chart_ptr->processes[i] == 0)
            break;
        working_time += chart_ptr->end[i] - chart_ptr->start[i];
        i++;
    }
    last_timeline = chart_ptr->end[i-1];
    throughput = (double) num_of_proc / last_timeline;
    cpu_utilization = (double) working_time / last_timeline * 100;

    for(i=0;i<num_of_proc; i++){
        total_turnaround_time += proc_list[i].done_time - proc_list[i].arrival;
        total_waiting_time += proc_list[i].waiting_time;
    }
    average_turnaround_time = (double) total_turnaround_time / num_of_proc;
    average_waiting_time = (double) total_waiting_time / num_of_proc;

    printf("Throughput : %lf / CPU Utilization : %lf%%\n", throughput, cpu_utilization);
    printf("Total / Average Turnaround Time : %lld / %lf\n", total_turnaround_time, average_turnaround_time);
    printf("Total / Average Waiting Time : %lld / %lf\n\n", total_waiting_time, average_waiting_time);
}