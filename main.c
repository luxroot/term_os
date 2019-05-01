#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"
#include "dllist.h"

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes]\n",argv[0]);
        exit(1);
    }
    int numOfProc=0;
    numOfProc = atoi(argv[1]);
    printf("aa : %d\n",numOfProc);

//    Process pc;
//    process_init(&pc, 3);
//
//    Queue qu;
//    queue_init(&qu);
//
//    enque(&qu, &pc);
//
//    queue_destroy(&qu);

    DLList dll;
    DLList_init(&dll);
    Node a[4];
    a[0].value = 3;
    a[1].value = 2;
    a[2].value = 5;
    a[3].value = 7;
    push_rear(&dll, &a[2]);
    push_rear(&dll, &a[1]);
    push_front(&dll, &a[0]);
    push_after(dll.nil.next, &a[3]);



    return 0;
}