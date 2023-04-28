#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_FIELD 128
#define MAX_RECORD 512

typedef struct{
    int fPathId;
    char* address;
    char* clueSa;
    char* assetType;
    double deltaZ;
    double distance;
    double grade1in;
    int mccId;
    int mccIdInt;
    double rLMax;
    double rLMin;
    char* segSide;
    int statusId;
    int streetId;
    int streetGroup;
    double startLat;
    double startLon;
    double endLat;
    double endLon;
}Record;

typedef struct Node{
    Record* data;
    struct Node* next;
}Node;

void freeList(Node* curr){
    Node* temp;
    while (curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp->data->address);
        free(temp->data->assetType);
        free(temp->data->clueSa);
        free(temp->data->segSide);
        free(temp->data);
        free(temp);
    }

}

int createInt(char* tmpField){
    int convert;
    convert = strtol(tmpField, NULL, 10);
    return convert;
}

double createDouble(char* tmpField){
    double convert;
    convert = strtod(tmpField, NULL);
    return convert;
}

char* createString(int right, int left, char* tmpField){
    char* string = calloc(strlen(tmpField) + 1, sizeof(char));
    strncpy(string, tmpField, (right - left));
    return string;
}

void fillRecordStruct(Record* structRec, int comma, char* tmpField, int right, int left){
    switch (comma){
        case 1:
            structRec->fPathId = createInt(tmpField);
            break;
        case 2:
            structRec->address = createString(right, left, tmpField);
            break;
        case 3:
            structRec->clueSa = createString(right, left, tmpField);
            break;
        case 4:
            structRec->assetType = createString(right, left, tmpField);
            break;
        case 5:
            structRec->deltaZ = createDouble(tmpField);
            break;
        case 6:
            structRec->distance = createDouble(tmpField);
            break;
        case 7:
            structRec->grade1in = createDouble(tmpField);
            break;
        case 8:
            structRec->mccId = createInt(tmpField);
            break;
        case 9:
            structRec->mccIdInt = createInt(tmpField);
            break;
        case 10:
            structRec->rLMax = createDouble(tmpField);
            break;
        case 11:
            structRec->rLMin = createDouble(tmpField);
            break;
        case 12:
            structRec->segSide = createString(right, left, tmpField);
            break;
        case 13:
            structRec->statusId = createInt(tmpField);
            break;
        case 14:
            structRec->streetId = createInt(tmpField);
            break;
        case 15:
            structRec->streetGroup = createInt(tmpField);
            break;
        case 16:
            structRec->startLat = createDouble(tmpField);
            break;
        case 17:
            structRec->startLon = createDouble(tmpField);
            break;
        case 18:
            structRec->endLat = createDouble(tmpField);
            break;
        default:
            printf("Error!!");
    }
}

Record* importRec(char* stringRec){
    Record* structRec = malloc(sizeof(Record));
    int right, left=0;
    int i=0, comma=1;
    bool quote = false;
    char tmpField[MAX_FIELD];
    memset(tmpField, '\0', MAX_FIELD);

    for (right=0; *stringRec != '\0'; right++, stringRec++){

        if (*stringRec == '"'){
            quote = quote ? false : true;
        }

        if (!quote && *stringRec == ','){

            fillRecordStruct(structRec, comma, tmpField, right, left);
            memset(tmpField, '\0', (right-left));
            left = right+1;
            i = 0; // reset tmpField iterator
            comma++;
            continue;
        }
        tmpField[i] = *stringRec;
        i++;
    }
    structRec->endLon = createDouble(tmpField);
    return structRec;
}

void insert(Node** head, Node** tail, char* currRec){
    Record* structRec = importRec(currRec); // create RECORD struct

    Node* newNode = malloc(sizeof(Node)); // create NODE for linked list
    newNode->data = structRec; // attach RECORD to NODE
    newNode->next = NULL; // nullify .next pointer

    // IF linked list is EMPTY
    if (!*head){
        *head = newNode;
        *tail = newNode;
        return;
    }

    // IF linked list only has a single node attached
    if (*head == *tail){
        (*head)->next = newNode;
        *tail = newNode;
        return;
    }

    // ELSE, IF linked list has more than one node in it.
    if (*head != *tail){
        (*tail)->next = newNode;
        *tail = newNode;
        return;
    }
}

void writeData(FILE* fpWrite, Node* curr){
    fprintf(fpWrite,"\tfPathID: %d\t||", curr->data->fPathId);
    fprintf(fpWrite,"\tAddress: %s\t||", strlen(curr->data->address) == 0 ? "EMPTY" : curr->data->address);
    fprintf(fpWrite,"\tClueSa: %s\t||", strlen(curr->data->clueSa) == 0 ? "EMPTY" : curr->data->clueSa);
    fprintf(fpWrite,"\tAssetType: %s\t||", strlen(curr->data->assetType) == 0 ? "EMPTY" : curr->data->assetType);
    fprintf(fpWrite,"\tDeltaZ: %f\t||", curr->data->deltaZ);
    fprintf(fpWrite,"\tDistance: %f\t||", curr->data->distance);
    fprintf(fpWrite,"\tGrade1in: %f\t||", curr->data->grade1in);
    fprintf(fpWrite,"\tMccID: %d\t||", curr->data->mccId);
    fprintf(fpWrite,"\tMccIDint: %d\t||", curr->data->mccIdInt);
    fprintf(fpWrite,"\tR_Lmax: %f\t||", curr->data->rLMax);
    fprintf(fpWrite,"\tR_Lmin: %f\t||", curr->data->rLMin);
    fprintf(fpWrite,"\tSegSide: %s\t||", strlen(curr->data->segSide) == 0 ? "EMPTY" : curr->data->segSide);
    fprintf(fpWrite,"\tStatusID: %d\t||", curr->data->statusId);
    fprintf(fpWrite,"\tStreetID: %d\t||", curr->data->streetId);
    fprintf(fpWrite,"\tStreetGroup: %d\t||", curr->data->streetGroup);
    fprintf(fpWrite,"\tStartLat: %f\t||", curr->data->startLat);
    fprintf(fpWrite,"\tStartLon: %f\t||", curr->data->startLon);
    fprintf(fpWrite,"\tEndLat: %f\t||", curr->data->endLat);
    fprintf(fpWrite,"\tEndLon: %f\n", curr->data->endLon);

}

void outputText(Node* curr, bool* exit, FILE* fpWrite){

    int i = 0;
    int value;

    char buffer[MAX_FIELD];
    memset(buffer, '\0', MAX_FIELD);
    printf("Enter Address:\t");
    fgets(buffer, sizeof(buffer), stdin);
    *buffer == '\n' ? fputs("(unfilled address)\n", fpWrite) : fputs(buffer, fpWrite);
    buffer[strlen(buffer) - 1] = '\0'; // This line is to overwrite the trailing '\n'.


    if (feof(stdin)){
        *exit = true;
        return;
    }

    while (curr){
        value = strcmp(buffer, curr->data->address);
        if (value == 0) {
            writeData(fpWrite, curr);
            i++;
        }
        curr = curr->next;
    }
    if (i == 0){
        fputs("\tNOTFOUND\n", fpWrite);
    }

    // STDOUT PRINT STATEMENT
    *buffer == '\0' ? printf("(unfilled address)") : printf("%s", buffer);
    i == 0 ? printf(" --> NOTFOUND\n") : printf(" --> %d\n", i);

}

int main(int argc, char** argv){

    Node* head = NULL; // Initialise linked list head,
    Node* tail = NULL; //   and tail.

    FILE* fpRead = fopen(*(argv + 1), "r"); // open file to be read

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        insert(&head, &tail, buffer); // create a node, fill it with record data & link it to linked list
    }
    fclose(fpRead); // close file

    FILE* fpWrite = fopen(*(argv + 2), "w"); // create txt file to be written
    bool exit = false; // used to exit out of loop
    while (!exit){
        // function used to output text to file & STDOUT
        outputText(head, &exit, fpWrite);
    }
    fclose(fpWrite); // close file

    printf("\n--PROGRAM ENDED--\n");
    // FREE MEMORY FOR EXIT
    freeList(head);


    return 0;
}