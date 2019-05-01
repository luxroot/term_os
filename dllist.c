#include "dllist.h"
#include <stddef.h>


void DLList_init(DLLptr dll){
    dll->nil = NULL;
}

void push_rear(DLLptr dll, NodePtr nptr){
    if(dll->nil == NULL){
        dll->nil->next = nptr;
        dll->nil->before = nptr;
        nptr->next = dll->nil;
        nptr->before = dll->nil;
    }
    else{

    }
}