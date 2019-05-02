#include "dllist.h"
#include <stddef.h>


void DLList_init(DLLptr dll){
    dll->nil.next = NULL;
    dll->nil.before = NULL;
    dll->nil.value = 0;
}

void push_back(DLLptr dll, NodePtr nptr){
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

NodePtr get_nth(DLLptr dll, unsigned int index){
    if(get_size(dll) <= index){
        return NULL;
    }
    NodePtr cur = dll->nil.next;
    while(index--){
        cur = cur->next;
    }
    return cur;
}

NodePtr pop_front(DLLptr dll){
    if(dll->nil.next == NULL)
        return NULL;
    else if(dll->nil.next == dll->nil.before){
        NodePtr cur = dll->nil.next;
        dll->nil.next = NULL;
        dll->nil.before = NULL;
        cur->next = NULL;
        cur->before = NULL;
        return cur;
    }
    else{
        NodePtr cur = dll->nil.next;
        dll->nil.next->next->before = &dll->nil;
        dll->nil.next = dll->nil.next->next;
        cur->next = NULL;
        cur->before = NULL;
        return cur;
    }
}

NodePtr pop_back(DLLptr dll){
    if(dll->nil.before == NULL){
        return NULL;
    }
    else if (dll->nil.next == dll->nil.before){
        NodePtr cur = dll->nil.next;
        dll->nil.next = NULL;
        dll->nil.before = NULL;
        cur->next = NULL;
        cur->before = NULL;
        return cur;
    }
    else{
        NodePtr cur = dll->nil.before;
        dll->nil.before->before->next = &dll->nil;
        dll->nil.before = dll->nil.before->before;
        cur->next = NULL;
        cur->before = NULL;
        return cur;
    }
}

NodePtr pop_this(NodePtr cur){
    if(cur == NULL)   return NULL;
    else if(cur->before == cur->next){
        NodePtr nil=cur->before;
        nil->before = NULL;
        nil->next = NULL;
        cur->before = NULL;
        cur->next = NULL;
        return cur;
    }
    else{
        cur->before->next = cur->next;
        cur->next->before = cur->before;
        cur->next = NULL;
        cur->before = NULL;
    }
}

NodePtr pop_nth(DLLptr dll, unsigned int index){
    unsigned int dll_size = get_size(dll);
    if(dll_size <= index){
        return NULL;
    }
    if(index == 0){
        return pop_front(dll);
    }
    else if (index == dll_size-1){
        return pop_back(dll);
    }
    else {
        return pop_this(get_nth(dll, index));
    }
}