#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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
    void* data;
    struct Node* next;
}Node;

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
    if (string == NULL){
        printf("Error: Out of memory\n");
        exit(-1);
    }
    strncpy(string, tmpField, (right - left));
    tmpField[right-left] = '\0';
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
    if (structRec == NULL){
        printf("Error: Out of memory\n");
        exit(-1);
    }
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

void freeRecordData(void* voidData){
    Record* data = voidData;
    free(data->address);
    free(data->assetType);
    free(data->clueSa);
    free(data->segSide);
}

void insert(Node** head, Node** tail, void* data){

    Node* newNode = malloc(sizeof(Node)); // create NODE for linked list
    if (newNode == NULL){
        printf("Error: Out of memory\n");
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

void writeData(FILE* fpWrite, Node* curr){
    Record* data = curr->data;
    fprintf(fpWrite,"\tfPathID: %d\t||", data->fPathId);
    fprintf(fpWrite,"\tAddress: %s\t||", strlen(data->address) == 0 ? "EMPTY" : data->address);
    fprintf(fpWrite,"\tClueSa: %s\t||", strlen(data->clueSa) == 0 ? "EMPTY" : data->clueSa);
    fprintf(fpWrite,"\tAssetType: %s\t||", strlen(data->assetType) == 0 ? "EMPTY" : data->assetType);
    fprintf(fpWrite,"\tDeltaZ: %f\t||", data->deltaZ);
    fprintf(fpWrite,"\tDistance: %f\t||", data->distance);
    fprintf(fpWrite,"\tGrade1in: %f\t||", data->grade1in);
    fprintf(fpWrite,"\tMccID: %d\t||", data->mccId);
    fprintf(fpWrite,"\tMccIDint: %d\t||", data->mccIdInt);
    fprintf(fpWrite,"\tR_Lmax: %f\t||", data->rLMax);
    fprintf(fpWrite,"\tR_Lmin: %f\t||", data->rLMin);
    fprintf(fpWrite,"\tSegSide: %s\t||", strlen(data->segSide) == 0 ? "EMPTY" : data->segSide);
    fprintf(fpWrite,"\tStatusID: %d\t||", data->statusId);
    fprintf(fpWrite,"\tStreetID: %d\t||", data->streetId);
    fprintf(fpWrite,"\tStreetGroup: %d\t||", data->streetGroup);
    fprintf(fpWrite,"\tStartLat: %f\t||", data->startLat);
    fprintf(fpWrite,"\tStartLon: %f\t||", data->startLon);
    fprintf(fpWrite,"\tEndLat: %f\t||", data->endLat);
    fprintf(fpWrite,"\tEndLon: %f\n", data->endLon);

}

void outputText(Node* curr, bool* exit, FILE* fpWrite){

    int i = 0;
    int value;

    char buffer[MAX_FIELD];
    memset(buffer, '\0', MAX_FIELD);
    printf("Enter Address:\t");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        *exit = true;
        return;
    };
    *buffer == '\n' ? fputs("(unfilled address)\n", fpWrite) : fputs(buffer, fpWrite);
    buffer[strlen(buffer) - 1] = '\0'; // This line is to overwrite the trailing '\n'.


    while (curr){
        Record* data = curr->data;
        value = strcmp(buffer, data->address);
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
    Record* data = NULL;

    FILE* fpRead = fopen("dataset_2.csv", "r"); // open file to be read

    fscanf(fpRead, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    while(fgets(buffer, MAX_RECORD, fpRead) != NULL){
        data = importRec(buffer);
        insert(&head, &tail, data); // create a node, fill it with record data & link it to linked list
    }
    fclose(fpRead); // close file


    FILE* fpWrite = fopen("output.txt", "w"); // create txt file to be written
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