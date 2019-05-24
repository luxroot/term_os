
#ifndef TERM_CHART_H
#define TERM_CHART_H

typedef struct _Chart{
    unsigned int timelines[1000];
    unsigned int processes[1000];
}Chart;

typedef Chart *ChartPtr;

#endif //TERM_CHART_H
