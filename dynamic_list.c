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
    if (!head){ // if malloc fails head will return NULL.
        return NULL;
    }
    void* list = malloc(sizeof(void*)*10);
    if (!list){
        return NULL; // if malloc fails head->data will return NULL.
    }
    head->data = list;
    head->size = 10;
    head->filled = 0;
    return head;
}

int appendList(ListHead* head, void* data){
    size_t filled = head->filled;
    size_t size = head->size;
    if (size - (filled + 1) < 2){

        void* temp = realloc(head->data, sizeof(void*) * (size * 2));

        // If realloc fails, then return -1 & add NULL to end of list.
        if (!temp){
            head->data[filled] = NULL;
            return -1;
        }
        head->data = temp; // else, if realloc successful, then head->data is "appended".
        head->size *= 2;
    }

    head->data[filled] = data;
    head->filled++;

    return 0;
}

