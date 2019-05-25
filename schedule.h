
#ifndef TERM_SCHEDULE_H
#define TERM_SCHEDULE_H

#include "dllist.h"
#include "chart.h"
#include <stddef.h>

void do_FCFS(uint, DLLptr, ChartPtr);

void do_nonpreemptive_SFJ(uint , DLLptr , ChartPtr);

#endif //TERM_SCHEDULE_H
