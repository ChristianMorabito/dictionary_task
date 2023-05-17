#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node{
    void* data;
    struct Node* next;
}Node;

void freeList(Node* curr, void(freeData)(void* data));

void insert(Node** head, Node** tail, void* data);


#endif // LINKED_LIST_H
