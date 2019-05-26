
#ifndef TERM_SCHEDULE_H
#define TERM_SCHEDULE_H

#include <stddef.h>

#include "dllist.h"
#include "chart.h"

void do_FCFS(uint, DLLptr, ChartPtr);
void do_nonpreemptive_SFJ(uint , DLLptr , ChartPtr);
void do_preemptive_SFJ(uint , DLLptr , ChartPtr);
void do_nonpreemptive_priority(uint , DLLptr , ChartPtr);
void do_preemptive_priority(uint , DLLptr , ChartPtr);

#endif //TERM_SCHEDULE_H
