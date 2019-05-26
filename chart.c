#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chart.h"

unsigned int *findValue(unsigned int* start, unsigned int* end, unsigned int value){
    unsigned int* ptr=start;
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
    unsigned int tl_idx_odd=1, tl_idx_even=0;
    unsigned int timelines[2000] = {0};
    char buffer[10]={0};

    i=0;
    while(1){
        if(chart_ptr->processes[i] == 0)
            break;
        printf("pid : %d %d ~ %d\n",chart_ptr->processes[i],chart_ptr->start[i],chart_ptr->end[i]);
        i++;
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

    for(i=0;i<lastTimeline/lines+1;i++){
        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(cur == timelines[tl_idx_even]){
                tl_idx_even+=2;
                sprintf(buffer,"%d",cur);
                printf("%s",buffer);
                j += strlen(buffer)-1;
            }
            else{
                printf(" ");
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");

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
            unsigned int *ptr = findValue(chart_ptr->start,chart_ptr->start+100,cur);
            unsigned int value;
            if(ptr != NULL){
                value = *ptr;
                printf("%d", value);
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");

        for(j=0;j<lines;j++){
            cur = i*lines + j;
            if(timelines[tl_idx_for_lower_tl] == cur){
                tl_idx_for_lower_tl++;
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
            if(cur == timelines[tl_idx_odd]){
                tl_idx_odd+=2;
                sprintf(buffer,"%d",cur);
                printf("%s",buffer);
                j += strlen(buffer)-1;
            }
            else{
                printf(" ");
            }
            if(cur == lastTimeline)
                break;
        }
        puts("");
    }

}