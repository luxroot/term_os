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

void DLList_init(DLList* dll);

#endif //TERM_DLLIST_H
