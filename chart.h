
#ifndef TERM_CHART_H
#define TERM_CHART_H

typedef struct _Chart{
    unsigned int start[2000];
    unsigned int end[2000];
    unsigned int processes[1000];
}Chart;

typedef Chart *ChartPtr;

#endif //TERM_CHART_H
