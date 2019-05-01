#ifndef TERM_QUEUE_H
#define TERM_QUEUE_H

#include "process.h"

#define QUEUE_CAPACIVITY 100

typedef struct _Queue{
    uint front;
    uint back;
    procPtr* procList;
} Queue;

typedef Queue *Qptr;

void queue_init(Qptr);
void queue_destroy(Qptr qptr);
uint full(Qptr);
uint empty(Qptr);
void enque(Qptr, procPtr item);
procPtr deque(Qptr);


#endif //TERM_QUEUE_H