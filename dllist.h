#ifndef TERM_DLLIST_H
#define TERM_DLLIST_H


typedef struct _Node{
    int value;
    struct _Node* before;
    struct _Node* next;
} Node;

typedef Node *NodePtr;

typedef struct _DLList{
    NodePtr nil;
}DLList;

typedef DLList *DLLptr;

void DLList_init(DLLptr);
void push_rear(DLLptr, NodePtr);
void push_front(DLLptr, NodePtr);
void push_after(NodePtr, NodePtr);

NodePtr pop_front(DLLptr);
NodePtr pop_rear(DLLptr);
NodePtr pop_this(NodePtr);

NodePtr get_front(DLLptr);
NodePtr get_rear(DLLptr);
NodePtr get_nth(DLLptr, uint);

uint get_size(DLLptr);


#endif //TERM_DLLIST_H
