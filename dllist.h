#ifndef TERM_DLLIST_H
#define TERM_DLLIST_H

typedef int Container;

typedef struct _Node{
    Container value;
    struct _Node* before;
    struct _Node* next;
} Node;

typedef Node *NodePtr;

typedef struct _DLList{
    Node nil;
}DLList;

typedef DLList *DLLptr;

void DLList_init(DLLptr);
void push_back(DLLptr dll, NodePtr nptr);
void push_front(DLLptr, NodePtr);
void push_after(NodePtr, NodePtr);

NodePtr pop_front(DLLptr);
NodePtr pop_back(DLLptr);
NodePtr pop_this(NodePtr);

NodePtr get_front(DLLptr);
NodePtr get_rear(DLLptr);
NodePtr get_nth(DLLptr, unsigned int);

unsigned int get_size(DLLptr);

#endif //TERM_DLLIST_H
