#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include <stdlib.h>
#include "data.h"

typedef struct{
    size_t filled;
    size_t size;
    void** data;
}ListHead;

ListHead* createHead();

void appendList(ListHead* head, void* data);

void freeDynamicList(ListHead** head, void(freeData)(void* data));


#endif // DYNAMIC_LIST_H