
#ifndef TERM_SCHEDULE_H
#define TERM_SCHEDULE_H

#include <stddef.h>

#include "dllist.h"
#include "chart.h"

void do_FCFS(uint, DLLptr, ChartPtr);
void do_non_preemptive_SFJ(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr);
void do_preemptive_SFJ(uint , DLLptr , ChartPtr);
void do_non_preemptive_priority(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr);
void do_preemptive_priority(uint , DLLptr , ChartPtr);
void do_round_robin(uint, DLLptr, ChartPtr, uint);
void do_non_preemptive_HRRN(uint num_of_proc, DLLptr job_queue, ChartPtr chart_ptr);
void do_preemptive_HRRN(uint , DLLptr , ChartPtr);
void do_preemptive_HRRN_atomic(uint , DLLptr , ChartPtr);
void do_dynamic_priority(uint , DLLptr , ChartPtr);
void do_custom_priority(uint , DLLptr , ChartPtr);

#endif //TERM_SCHEDULE_H
