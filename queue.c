#include "queue.h"
#include <stddef.h>
#include <stdlib.h>

void queue_init(Qptr qptr){
    qptr->back=0;
    qptr->front=0;
    qptr->procList=(procPtr*)malloc(sizeof(Process)*QUEUE_CAPACIVITY);
}

void queue_destroy(Qptr qptr){
    free(qptr->procList);
}

uint full(Qptr qptr){
    if((qptr->back+1) % QUEUE_CAPACIVITY == qptr->front){
        return 1;
    }
    else{
        return 0;
    }
}

uint empty(Qptr qptr){
    if(qptr->front == qptr->back){
        return 1;
    }
    else{
        return 0;
    }
}

void enque(Qptr qptr, procPtr item){
    qptr->procList[qptr->back] = item;
    (qptr->back)++;
    (qptr->back)%=QUEUE_CAPACIVITY;
}

procPtr deque(Qptr qptr){
    if(qptr->front==0){
        qptr->front = QUEUE_CAPACIVITY-1;
        return qptr->procList[0];
    }
    else{
        (qptr->front)++;
        return qptr->procList[(qptr->front)-1];
    }
}