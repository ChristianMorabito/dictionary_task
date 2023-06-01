#include <stdio.h>
#include "dynamic_list.h"

void freeDynamicList(ListHead** head, void(freeData)(void* data)){

    void** curr = (*head)->data;
    void** temp;

    while (*curr){ // the last filled item is pointing to NULL, hence why the loop will stop at NULL.
        temp = curr;
        curr++;
        freeData(*temp); // free data inside the node that the array pointer is pointing to.
        free(*temp); // free the node that the array pointer is pointing to.
    }
    free((*head)->data); // free the dynamic array.
    free(*head); // free the list head.
}

ListHead* createHead(){
    ListHead* head = malloc(sizeof(ListHead));
    void* list = malloc(sizeof(void*)*10);
    head->data = list;
    head->size = 10;
    head->filled = 0;
    return head;
}

void appendList(ListHead** head, void* data){
    size_t filled = (*head)->filled;
    size_t size = (*head)->size;
    if (size - (filled + 1) < 1){
        (*head)->data = realloc((*head)->data, sizeof(void*) * (size * 2));
        if ((*head)->data == NULL){
            printf("REALLOC FAILED");
            exit(-1);
        }
        (*head)->size *= 2;
    }
    (*head)->data[filled] = data;
    (*head)->filled++;
}

