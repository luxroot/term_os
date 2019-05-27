#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chart.h"

const unsigned int *findValue(const unsigned int* start, const unsigned int* end, unsigned int value){
    const unsigned int* ptr=start;
    while(ptr <= end){
        if(*ptr == value)
            return ptr;
        ptr++;
    }
    return NULL;
}

void drawChart(ChartPtr chart_ptr, unsigned int lines){
    unsigned int tl_idx=3, i=0, totalTimelines=0, lastTimeline=0, j, cur=0, chart_idx = 1;
    unsigned int tl_idx_for_upper_tl = 0, tl_idx_for_lower_tl = 0;
    unsigned int tl_idx_odd=1, tl_idx_even=0, exit_loop=0;
    unsigned int timelines[2000] = {0};
    char buffer[10]={0};

    for(i=0;;i++){
        for(j=0;j<4;j++){
            cur = i*4+j;
            if(chart_ptr->processes[cur] == 0) {
                exit_loop = 1;
                break;
            }
            printf("pid : %-3d%4d ~ %-4d| ",chart_ptr->processes[cur],chart_ptr->start[cur],chart_ptr->end[cur]);
        }
        puts("");
        if(exit_loop){
            break;
        }
    }

    if(chart_ptr->start[0] == 0) {
        timelines[1] = chart_ptr->end[0];
        tl_idx--;
    }
    else {
        timelines[1] = chart_ptr->start[0];
        timelines[2] = chart_ptr->end[0];
    }

    while(chart_ptr->processes[chart_idx] != 0){
        if(timelines[tl_idx-1] != chart_ptr->start[chart_idx]){
            timelines[tl_idx++] = chart_ptr->start[chart_idx];
        }
        timelines[tl_idx++] = chart_ptr->end[chart_idx];
        chart_idx++;
    }
    totalTimelines = tl_idx;
    lastTimeline = timelines[totalTimelines-1];

    chart_idx=0;
    for(i=0;i<lastTimeline/lines+1;i++){
        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(cur == timelines[tl_idx_odd]){
                tl_idx_odd+=2;
                sprintf(buffer,"%d",cur);
                printf("%-6s",buffer);
                j++;
            }
            else{
                printf("   ");
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(cur == lastTimeline) {
                printf("+");
                break;
            }
            else if(timelines[tl_idx_for_upper_tl] == cur){
                tl_idx_for_upper_tl++;
                printf("+--");
            }
            else {
                printf("---");
            }
        }
        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(chart_ptr->start[chart_idx] == cur){
                sprintf(buffer,"|%-2d",chart_ptr->processes[chart_idx]);
                chart_idx++;
                printf("%s",buffer);
            }
            else if(findValue(timelines, timelines+totalTimelines, cur)){
                printf("|  ");
            }
            else{
                printf("   ");
            }
            if(cur == lastTimeline) {
                break;
            }
        }
        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(cur == lastTimeline) {
                printf("+");
                break;
            }
            else if(timelines[tl_idx_for_lower_tl] == cur){
                tl_idx_for_lower_tl++;
                printf("+--");
            }
            else{
                printf("---");
            }
        }

        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(cur == timelines[tl_idx_even]){
                tl_idx_even+=2;
                sprintf(buffer,"%-6d",cur);
                printf("%s",buffer);
                j++;
            }
            else{
                printf("   ");
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");
    }

}