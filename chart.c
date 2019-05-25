
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chart.h"

void drawChart(ChartPtr chart_ptr, unsigned int numOfProc, unsigned int lines){
    unsigned int tl_idx=3, i=0, totalTimelines=0, lastTimeline=0, j, cur=0, chart_idx = 1;
    unsigned int tl_idx_for_upper_tl = 0, tl_idx_for_lower_tl = 0, tl_idx_for_mid_tl = 0;
    unsigned int timelines[2000] = {0};
    char buffer[10]={0};

    timelines[1] = chart_ptr->start[0];
    timelines[2] = chart_ptr->end[0];
    while(chart_ptr->processes[chart_idx] != 0){
        if(timelines[tl_idx-1] != chart_ptr->start[chart_idx]){
            timelines[tl_idx++] = chart_ptr->start[chart_idx];
        }
        timelines[tl_idx++] = chart_ptr->end[chart_idx];
        chart_idx++;
    }
    totalTimelines = tl_idx;
    lastTimeline = timelines[totalTimelines-1];
    chart_idx = 0;

    for(i=0;i<lastTimeline/lines+1;i++){
        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(timelines[tl_idx_for_upper_tl] == cur){
                tl_idx_for_upper_tl++;
                printf("+");
            }
            else{
                printf("-");
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(timelines[tl_idx_for_mid_tl] == cur){
                tl_idx_for_mid_tl++;
                printf("|");
            }
            else{
                printf(" ");
            }
            if(chart_ptr->start[chart_idx]+1 == cur){
                sprintf(buffer,"%d",chart_ptr->processes[chart_idx]);
                printf("%s",buffer);
                j += strlen(buffer);
                chart_idx++;
            }
        }
        puts("");

        for(j=0;j<lines;j++){
            if(cur == lastTimeline)
                break;
            cur = i*lines + j;
            if(timelines[tl_idx_for_lower_tl] == cur){
                tl_idx_for_lower_tl++;
                printf("+");
            }
            else{
                printf("-");
            }
        }
        puts("");
        puts("");
    }

}