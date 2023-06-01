#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "dynamic_list.h"
#include "sort.h"
#define MAX_RECORD 512


int main(int argv, char* argc[]){
    Record* data = NULL;
    ListHead* head = createHead();

    FILE* fpRead = fopen(argc[1], "r"); // open file to be read
    if (fpRead == NULL){
        printf("File could not be opened! Exiting...\n");
        exit(-1);
    }

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    int i = 0; //
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        data = importRec(buffer);
        appendList(&head, data);
        i++;
    }
    appendList(&head, NULL);
    fclose(fpRead); // close file

//  SORT
    divide((Record** )(head->data), 0, i-1);

    FILE* fpWrite = fopen(argc[2], "w"); // create txt file to be written
    if (fpWrite == NULL){
        printf("File could not be written! Exiting...\n");
        exit(-1);
    }

    while (outputText(head->data, fpWrite, outputDynamicList)){
    }

    fclose(fpWrite); // close file

    printf("\n--PROGRAM ENDED--\n");
//  FREE MEMORY FOR EXIT
    freeDynamicList(&head, freeRecordData);


    return 0;
}