#ifndef TERM_QUEUE_H
#define TERM_QUEUE_H

#include "process.h"

#define QUEUE_CAPACIVITY 100

typedef Process* Queue_Container;

typedef struct _Queue{
    uint front;
    uint back;
    Queue_Container* procList;
} Queue;

typedef Queue *Qptr;

void queue_init(Qptr);
void queue_destroy(Qptr);
uint full(Qptr);
uint empty(Qptr);
void enque(Qptr, Queue_Container);
Queue_Container deque(Qptr);


#endif //TERM_QUEUE_H