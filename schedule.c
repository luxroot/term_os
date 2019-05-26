#include <stdlib.h>
#include <string.h>

#include "schedule.h"
#include "chart.h"

void add_waiting_times(DLLptr wq_ptr){
    uint i=0;
    for(i=0;i<get_size(wq_ptr);i++){
        get_nth(wq_ptr, i)->value->waiting_time++;
    }
}

void do_FCFS(uint numOfProc, DLLptr job_queue, ChartPtr chart_ptr){
    if(get_size(job_queue)==0){
        return;
    }
    DLList waiting_queue;
    DLLptr wq_ptr = &waiting_queue;
    DLList_init(wq_ptr);

    NodePtr nodeList = (NodePtr) malloc(sizeof(Node) * numOfProc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                nodeList[node_index].value = get_nth(job_queue, i)->value;
                push_back(wq_ptr, &nodeList[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job
        if (current_job == NULL && get_size(wq_ptr) != 0) {
            current_job = get_front(wq_ptr);
            pop_front(wq_ptr);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->bursted++;

            // Check done
            if (current_job->value->bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(wq_ptr);

        // Check FCFS has ended
        if(get_size(job_queue) == 0 && get_size(wq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(nodeList);
}

void do_nonpreemptive_SFJ(uint numOfProc, DLLptr job_queue, ChartPtr chart_ptr){
    if(get_size(job_queue)==0){
        return;
    }
    DLList waiting_queue;
    DLLptr wq_ptr = &waiting_queue;
    DLList_init(wq_ptr);

    NodePtr nodeList = (NodePtr) malloc(sizeof(Node) * numOfProc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                nodeList[node_index].value = get_nth(job_queue, i)->value;
                push_back(wq_ptr, &nodeList[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(wq_ptr) != 0) {
            current_job = get_front(wq_ptr);
            int min_idx = 0;
            for(i=0;i<get_size(wq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(wq_ptr, i)->value->cpu_burst < current_job->value->cpu_burst){
                    current_job = get_nth(wq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(wq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->bursted++;

            // Check done
            if (current_job->value->bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(wq_ptr);

        // Check nonP_SJF has ended
        if(get_size(job_queue) == 0 && get_size(wq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(nodeList);
}


void do_preemptive_SFJ(uint numOfProc, DLLptr job_queue, ChartPtr chart_ptr){
    if(get_size(job_queue)==0){
        return;
    }
    DLList waiting_queue;
    DLLptr wq_ptr = &waiting_queue;
    DLList_init(wq_ptr);

    NodePtr nodeList = (NodePtr) malloc(sizeof(Node) * numOfProc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                nodeList[node_index].value = get_nth(job_queue, i)->value;
                push_back(wq_ptr, &nodeList[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(wq_ptr) != 0) {
            current_job = get_front(wq_ptr);
            int min_idx = 0;
            for(i=0;i<get_size(wq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(wq_ptr, i)->value->cpu_burst < current_job->value->cpu_burst){
                    current_job = get_nth(wq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(wq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->bursted++;

            // Check done
            if (current_job->value->bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(wq_ptr);

        // Check nonP_SJF has ended
        if(get_size(job_queue) == 0 && get_size(wq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(nodeList);
}



