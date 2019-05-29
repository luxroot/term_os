#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "schedule.h"
#include "chart.h"
#include "queue.h"
#include "dllist.h"


void add_waiting_times(DLLptr rdq_ptr){
    uint i=0;
    for(i=0;i<get_size(rdq_ptr);i++){
        get_nth(rdq_ptr, i)->value->waiting_time++;
    }
}

void burst_io(DLLptr ioq_ptr, DLLptr rdq_ptr, NodePtr rd_queue_node_list){
    uint i=0, queue_size=get_size(ioq_ptr);
    if(queue_size == 0)
        return;
    ProcPtr cur=NULL;
    for(i=0;i<get_size(ioq_ptr);i++){
        cur = get_nth(ioq_ptr, i)->value;
        cur->io_bursted++;
        cur->waiting_time++;
        if(cur->io_burst - cur->io_bursted == 0){
            pop_nth(ioq_ptr, i);
            i--;
            push_back(rdq_ptr, get_using_proc_ptr(rd_queue_node_list, cur));
            continue;
        }
        if(cur->cpu_burst - cur->cpu_bursted!=1){
            pop_nth(ioq_ptr, i);
            i--;
            push_back(rdq_ptr, get_using_proc_ptr(rd_queue_node_list, cur));
        }
    }
}

void do_FCFS(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    DLList io_queue;
    DLLptr ioq_ptr = &io_queue;
    DLList_init(ioq_ptr);

    NodePtr io_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Random I/O
        if(current_job && current_job->value->io_burst - current_job->value->io_bursted){
            if(current_job->value->cpu_burst - current_job->value->cpu_bursted==1){
                current_job->value->first_io = current_job->value->io_bursted;
                push_back(ioq_ptr, current_job);
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
            else if(rand() % 3 == 0){
                current_job->value->first_io = current_job->value->io_bursted;
                push_back(ioq_ptr, current_job);
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        // Check idle CPU & waiting job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            pop_front(rdq_ptr);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        add_waiting_times(rdq_ptr);
        burst_io(ioq_ptr, rdq_ptr, rd_queue_node_list);

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }


        // Check FCFS has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && get_size(ioq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
    free(io_queue_node_list);
}

void do_non_preemptive_SFJ(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->cpu_burst < current_job->value->cpu_burst){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check nonP_SJF has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


void do_preemptive_SFJ(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    NodePtr new_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->cpu_burst < current_job->value->cpu_burst){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }
        // Check current working process & waiting job -> find shorter job
        else if (current_job != NULL && get_size(rdq_ptr) != 0) {
            new_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->cpu_burst < new_job->value->cpu_burst - new_job->value->cpu_bursted){
                    new_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            if(current_job->value != new_job->value && new_job->value->cpu_burst - new_job->value->cpu_bursted < current_job->value->cpu_burst - current_job->value->cpu_bursted){
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                pop_nth(rdq_ptr, min_idx);
                push_back(rdq_ptr, current_job);
                current_job = new_job;
                chart_ptr->start[chart_index] = current_time;
            }
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check P_SJF has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


void do_non_preemptive_priority(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->priority < current_job->value->priority){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check nonP_Priority has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


void do_preemptive_priority(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    NodePtr new_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->priority < current_job->value->priority){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }
            // Check current working process & waiting job -> find shorter job
        else if (current_job != NULL && get_size(rdq_ptr) != 0) {
            new_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(get_nth(rdq_ptr, i)->value->priority < new_job->value->priority){
                    new_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            if(current_job->value != new_job->value && new_job->value->priority < current_job->value->priority){
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                pop_nth(rdq_ptr, min_idx);
                push_back(rdq_ptr, current_job);
                current_job = new_job;
                chart_ptr->start[chart_index] = current_time;
            }
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check P_Priority has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


void do_round_robin(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr, uint time_quantum){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            pop_front(rdq_ptr);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;
            current_job->value->quantum++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
            else if (current_job->value->quantum >= time_quantum && get_size(rdq_ptr) > 0){
                current_job->value->quantum = 0;
                push_back(rdq_ptr, current_job);
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check RR has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


double get_HRRN_priority(NodePtr a){
    return (double) (a->value->waiting_time + a->value->cpu_burst - a->value->cpu_bursted) / (a->value->cpu_burst - a->value->cpu_bursted);
}

int is_higher_HRRN(NodePtr a, NodePtr b){
    if(get_HRRN_priority(a) > get_HRRN_priority(b))
        return 1;
    else
        return 0;
}


void do_non_preemptive_HRRN(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(is_higher_HRRN(get_nth(rdq_ptr, i), current_job)){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check nonP_HRRN has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}


void do_preemptive_HRRN(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr){
    DLList ready_queue;
    DLLptr rdq_ptr = &ready_queue;
    DLList_init(rdq_ptr);

    NodePtr rd_queue_node_list = (NodePtr) malloc(sizeof(Node) * num_of_proc);

    NodePtr current_job = NULL;
    NodePtr new_job = NULL;
    uint current_time=0;
    uint i=0;
    uint chart_index = 0;
    uint node_index = 0;

    while(1){
        // Push arrived tasks into waiting queue
        for(i=0;i<get_size(job_queue);i++) {
            if (get_nth(job_queue, i)->value->arrival == current_time) {
                rd_queue_node_list[node_index].value = get_nth(job_queue, i)->value;
                push_back(rdq_ptr, &rd_queue_node_list[node_index++]);
                pop_nth(job_queue, i--);
            }
        }

        // Check idle CPU & waiting job -> select appropriate job
        if (current_job == NULL && get_size(rdq_ptr) != 0) {
            current_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select Highest HRRN priority job
                if(is_higher_HRRN(get_nth(rdq_ptr, i), current_job)){
                    current_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            pop_nth(rdq_ptr, min_idx);
            chart_ptr->start[chart_index] = current_time;
        }
        // Check current working process & waiting job -> find shorter job
        else if (current_job != NULL && get_size(rdq_ptr) != 0) {
            new_job = get_front(rdq_ptr);
            unsigned int min_idx = 0;
            for(i=0;i<get_size(rdq_ptr);i++){
                // Select minimum cpu_burst job
                if(is_higher_HRRN(get_nth(rdq_ptr, i), new_job)){
                    new_job = get_nth(rdq_ptr, i);
                    min_idx = i;
                }
            }
            if(current_job->value != new_job->value && is_higher_HRRN(new_job, current_job)){
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                pop_nth(rdq_ptr, min_idx);
                push_back(rdq_ptr, current_job);
                current_job = new_job;
                chart_ptr->start[chart_index] = current_time;
            }
        }

        current_time++;

        // Check busy CPU
        if(current_job != NULL) {
            current_job->value->cpu_bursted++;

            // Check done
            if (current_job->value->cpu_bursted == current_job->value->cpu_burst) {
                current_job->value->done_time = current_time;
                chart_ptr->processes[chart_index] = current_job->value->pid;
                chart_ptr->end[chart_index] = current_time;
                chart_index++;
                current_job = NULL;
            }
        }

        add_waiting_times(rdq_ptr);

        // Check P_HRRN has ended
        if(get_size(job_queue) == 0 && get_size(rdq_ptr)==0 && current_job == NULL)
            break;
    }

    // Free dynamically allocated variable
    free(rd_queue_node_list);
}