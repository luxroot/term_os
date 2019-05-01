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

NodePtr get_front(DLLptr dll){
    return dll->nil.next;
}

NodePtr get_rear(DLLptr dll){
    return dll->nil.before;
}

unsigned int get_size(DLLptr dll){
    if(dll->nil.next == NULL){
        return 0;
    }
    unsigned int size=1;
    NodePtr cur = dll->nil.next;
    while(cur->next != &dll->nil){
        size++;
        cur = cur->next;
    }
    return size;
}

NodePtr get_nth(DLLptr dll, unsigned int n){
    if(get_size(dll) < n){
        return NULL;
    }
    NodePtr cur = dll->nil.next;
    while(n--){
        cur = cur->next;
    }
    return cur;
}

NodePtr pop_front(DLLptr dll){
    if(dll->nil.next == NULL)
        return NULL;
    else if(dll->nil.next == dll->nil.before){
        DLLptr cur = dll->nil.next;
        dll->nil.next = NULL;
        dll->nil.before = NULL;
        return cur;
    }
    else{
        DLLptr cur = dll->nil.next;
        dll->nil.next->before = &dll->nil;
        dll->nil.next = dll->nil.next->next;
        return cur;
    }
}

//NodePtr pop_rear(){
//    if(dll->)
//}