#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"

int main(int argc, void** argv){
    if(argc < 2){
        fprintf(stderr,"usage : %s [number of processes]\n",(char*)argv[0]);
        exit(1);
    }
    int numOfProc=0;
    numOfProc = atoi(argv[1]);
    printf("aa : %d\n",numOfProc);
}