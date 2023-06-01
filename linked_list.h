#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node{
    void* data;
    struct Node* next;
}Node;

typedef struct{
    Node* head;
    Node* tail;
}LinkedList;


LinkedList* create();

void freeLinkedList(LinkedList* linkedList, void(freeData)(void* data));

void insert(LinkedList* linkedList, void* data);


#endif // LINKED_LIST_H