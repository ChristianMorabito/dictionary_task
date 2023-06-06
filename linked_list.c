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

int insert(LinkedList* linkedList, void* data){

    Node* newNode = malloc(sizeof(Node)); // create NODE for linked list
    // if malloc fails...
    if (newNode == NULL){
        return -1; // then return -1
    }
    newNode->data = data; // attach RECORD to NODE
    newNode->next = NULL; // nullify .next pointer

    // IF linked list is EMPTY
    if (!linkedList->head){
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }

    else{
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }
    return 0;

}

LinkedList* create(){

    LinkedList* linkedList = malloc(sizeof(LinkedList));
    if (linkedList == NULL){
        return NULL; // if malloc fails
    }
    linkedList->head = NULL;
    linkedList->tail = NULL;

    return linkedList;
}