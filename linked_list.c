#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void freeList(Node* curr, void(freeData)(void* data)){
    Node* temp;
    while (curr != NULL){
        temp = curr;
        curr = curr->next;
        freeData(temp->data);
        free(temp->data);
        free(temp);
    }
}

void insert(Node** head, Node** tail, void* data){

    Node* newNode = malloc(sizeof(Node)); // create NODE for linked list
    if (newNode == NULL){
        printf("Error: Out of memory. Exiting...\n");
        exit(-1);
    }
    newNode->data = data; // attach RECORD to NODE
    newNode->next = NULL; // nullify .next pointer

    // IF linked list is EMPTY
    if (!*head){
        *head = newNode;
        *tail = newNode;
        return;
    }

    else {
        (*tail)->next = newNode;
        *tail = newNode;
        return;
    }
}

