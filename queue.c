#include "queue.h"
#include <stddef.h>
#include <stdlib.h>

// Initializing queue
void queue_init(Qptr qptr){
    qptr->back = 0;
    qptr->front = 0;
    qptr->procList = (Queue_Container*) malloc(sizeof(Queue_Container) * QUEUE_CAPACIVITY);
}

// Destroy queue
void queue_destroy(Qptr qptr){
    free(qptr->procList);
    qptr->procList = NULL;
    qptr->back = 0;
    qptr->front = 0;
}

// If circular queue is full than return 1(true) else 0
uint full(Qptr qptr){
    if((qptr->back+1) % QUEUE_CAPACIVITY == qptr->front){
        return 1;
    }
    else{
        return 0;
    }
}

// Returns 1 when queue is empty
uint empty(Qptr qptr){
    if(qptr->front == qptr->back){
        return 1;
    }
    else{
        return 0;
    }
}

// Enqueue variable
void enque(Qptr qptr, ProcPtr item){
    qptr->procList[qptr->back] = item;
    (qptr->back)++;
    (qptr->back) %= QUEUE_CAPACIVITY;
}

// Dequeue variable
Queue_Container deque(Qptr qptr){
    if(qptr->front == 0){
        qptr->front = QUEUE_CAPACIVITY-1;
        return qptr->procList[0];
    }
    else{
        (qptr->front)++;
        return qptr->procList[(qptr->front)-1];
    }
}