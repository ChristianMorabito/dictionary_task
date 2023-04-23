#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int createInt(char* tmpField){
    int converted;
    converted = strtol(tmpField, NULL, 10);
    return converted;
}

char* createString(int right, int left, char* tmpField){
    char* string = calloc(strlen(tmpField), sizeof(char));
    strncpy(string, tmpField, (right - left));
    return string;
}

double createDouble(char* tmpField){
    double converted;
    converted = strtod(tmpField, NULL);
    return converted;
}

void fillStructDescriptors(Record* structRec, int comma, char* tmpField, int right, int left){
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
    char tmpField[MAX_FIELD];
    memset(tmpField, '\0', MAX_FIELD);
    for (right=0; *stringRec != '\0'; right++, stringRec++){
        if (*stringRec == ','){
            fillStructDescriptors(structRec, comma, tmpField, right, left);
            memset(tmpField, '\0', (right-left)-1);
            left = right;
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

void insert(Node** head, char* strRec){
    // create struct Record
    Record* structRec = importRec(strRec);
    // create struct Node
    Node* newNode = malloc(sizeof(Node));
    newNode->data = structRec;
    newNode->next = NULL;

    if (!*head){
        *head = newNode;
        return;
    }
    // pointer that traverses from head, down the linked list
    Node* curr = *head;
    while (curr->next){
        curr = curr->next;
    }
    curr->next = newNode;
}

int main(){
    Node* head = NULL; // Head for Linked List

    FILE* fPtr; // Create file pointer & open file
    fPtr = fopen("dataset_20.csv", "r");

    fscanf(fPtr, "%*[^\n]\n"); // Bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through
    memset(buffer, '\0', MAX_RECORD); // initalise buffer array

    // while loop allows for the csv records/rows to be iterated through, until the end
    while(fgets(buffer,MAX_RECORD,fPtr) != NULL){
        // create a node, fill it with record data & link it to linked list
        insert(&head, buffer);
    }

    // DON'T FORGET TO FREE MEMORY!!
    fclose(fPtr);

    return 0;
}