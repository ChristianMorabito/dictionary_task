#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void freeLinkedList(LinkedList* linkedList, void(freeData)(void* data)){
    Node* curr = linkedList->head;
    Node* temp;
    while (curr != NULL){
        temp = curr;
        curr = curr->next;
        freeData(temp->data);
        free(temp->data);
        free(temp);
    }
    free(linkedList);
}

void insert(LinkedList* linkedList, void* data){

    Node* newNode = malloc(sizeof(Node)); // create NODE for linked list
    if (newNode == NULL){
        printf("Error: Out of memory. Exiting...\n");
        exit(-1);
    }
    newNode->data = data; // attach RECORD to NODE
    newNode->next = NULL; // nullify .next pointer

    // IF linked list is EMPTY
    if (!linkedList->head){
        linkedList->head = newNode;
        linkedList->tail = newNode;
        return;
    }

    else {
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
        return;
    }
}

LinkedList* create(){

    LinkedList* linkedList = malloc(sizeof(LinkedList));
    if (linkedList == NULL){
        printf("MALLOC FAILED. Exiting...\n");
        exit(-1);
    }
    linkedList->head = NULL;
    linkedList->tail = NULL;

    return linkedList;
}