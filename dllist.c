#include "dllist.h"
#include <stddef.h>


void DLList_init(DLLptr dll){
    dll->nil.next = NULL;
    dll->nil.before = NULL;
    dll->nil.value = 0;
}

void push_rear(DLLptr dll, NodePtr nptr){
    if(dll->nil.before == NULL){
        dll->nil.next = nptr;
        dll->nil.before = nptr;
        nptr->next = &dll->nil;
        nptr->before = &dll->nil;
    }
    else{
        dll->nil.before->next = nptr;
        nptr->before = dll->nil.before;
        nptr->next = &dll->nil;
        dll->nil.before = nptr;
    }
}

void push_front(DLLptr dll, NodePtr nptr){
    if(dll->nil.next == NULL){
        dll->nil.before = nptr;
        dll->nil.next = nptr;
        nptr->next = &dll->nil;
        nptr->before = &dll->nil;
    }
    else{
        dll->nil.next->before = nptr;
        nptr->next = dll->nil.next;
        nptr->before = &dll->nil;
        dll->nil.next = nptr;
    }
}

void push_after(NodePtr beforePtr, NodePtr afterPtr){
    beforePtr->next->before = afterPtr;
    afterPtr->next = beforePtr->next;
    beforePtr->next = afterPtr;
    afterPtr->before = beforePtr;
}

