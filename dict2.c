#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "dynamic_list.h"
#include "sort.h"
#define MAX_RECORD 512


int main(int argc, char* argv[]){
    Record* data = NULL;
    ListHead* head = createHead();
    if (!head || !head->data){
        puts("Memory failed. Exiting...\n");
        exit(-1);
    }

    FILE* fpRead = fopen(argv[1], "r"); // open file to be read
    if (fpRead == NULL){
        printf("File could not be opened! Exiting...\n");
        exit(-1);
    }

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    int i = 0; //
    int status;
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        data = importRec(buffer);
        status = appendList(head, data);
        if (status == -1){
            puts("Memory failed. Exiting...\n");
            exit(-1);
        }
        i++;
    }
    if (status == 0) {
        appendList(head, NULL); // add NULL 'end reference' to mark end of list.
    }
    fclose(fpRead); // close file

//  SORT
    quicksort((Record **)(head->data), 0, i - 1);

    FILE* fpWrite = fopen(argv[2], "w"); // create txt file to be written
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