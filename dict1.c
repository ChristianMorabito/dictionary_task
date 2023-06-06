#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "data.h"
#define MAX_RECORD 512


int main(int argc, char* argv[]){

    LinkedList* linkedList = create(); // initalise linkedList head & tail.
    if (!create){
        puts("Memory Allocation Failed! Exiting...\n");
    }

    Record* data = NULL;

    FILE* fpRead = fopen(argv[1], "r"); // open file to be read
    if (fpRead == NULL){
        puts("File could not be opened! Exiting...\n");
        exit(-1);
    }

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    int status;
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        data = importRec(buffer); // (1) create record node
        status = insert(linkedList, data); // (2) attach record node to linked list
        if (status == -1){
            puts("Memory Allocation Failed! Exiting...");
            exit(-1);
        }
    }
    fclose(fpRead); // close file


    FILE* fpWrite = fopen(argv[2], "w"); // create txt file to be written
    if (fpWrite == NULL){
        puts("File could not be written! Exiting...");
        exit(-1);
    }
    while (outputText((void *)linkedList, fpWrite, outputLinkedList)){
    }
    fclose(fpWrite); // close file

    printf("\n--PROGRAM ENDED--\n");
    //  FREE MEMORY FOR EXIT
    freeLinkedList(linkedList, freeRecordData);

    return 0;
}