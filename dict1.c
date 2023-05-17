
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "data.h"
#define MAX_RECORD 512



int main(int argc, char** argv){

    Node* head = NULL; // Initialise linked list head,
    Node* tail = NULL; //   and tail.
    Record* data = NULL;

    FILE* fpRead = fopen(*(argv + 1), "r"); // open file to be read
    if (fpRead == NULL){
        printf("File could not be opened! Exiting...");
        exit(-1);
    }

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        data = importRec(buffer);
        insert(&head, &tail, data); // create a node, fill it with record data & link it to linked list
    }
    fclose(fpRead); // close file


    FILE* fpWrite = fopen(*(argv + 2), "w"); // create txt file to be written
    if (fpWrite == NULL){
        printf("File could not be written! Exiting...");
        exit(-1);
    }
    bool exit = false; // used to exit out of loop
    while (!exit){
        // function used to output text to file & STDOUT
        outputText(head, &exit, fpWrite);
    }
    fclose(fpWrite); // close file

    printf("\n--PROGRAM ENDED--\n");
//  FREE MEMORY FOR EXIT
    freeList(head, freeRecordData);


    return 0;
}