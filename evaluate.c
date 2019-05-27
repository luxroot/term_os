#include <stdio.h>

#include "evaluate.h"

void printEvaluation(uint numOfProc, ProcPtr procList, ChartPtr chart_ptr){
    unsigned long long ttt=0, twt=0;
    unsigned int i=0, last_timeline, working_time=0;
    double att=0, awt=0, throughput=0, cpu_utilization=0;

    while(1){
        if(chart_ptr->processes[i] == 0)
            break;
        working_time += chart_ptr->end[i] - chart_ptr->start[i];
        i++;
    }
    last_timeline = chart_ptr->end[i-1];
    throughput = (double) last_timeline / numOfProc;
    cpu_utilization = (double) working_time / last_timeline * 100;

    for(i=0;i<numOfProc; i++){
        ttt += procList[i].done_time - procList[i].arrival;
        twt += procList[i].waiting_time;
    }
    att = (double) ttt / numOfProc;
    awt = (double) twt / numOfProc;

    printf("Throughput : %lf / CPU Utilization : %lf%%\n", throughput, cpu_utilization);
    printf("Total / Average Turnaround Time : %lld / %lf\n", ttt, att);
    printf("Total / Average Waiting Time : %lld / %lf\n\n", twt, awt);
}