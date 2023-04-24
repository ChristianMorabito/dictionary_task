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
    char* string = calloc(strlen(tmpField), sizeof(char));
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

void printList(Node* curr){
    int i = 1;
    while (curr){
        printf("\n__________________NODE %d__________________\n", i);
        printf("fPathID: %d\n",curr->data->fPathId);
        printf("Address: %s\n",strlen(curr->data->address) == 0 ? "EMPTY": curr->data->address);
        printf("ClueSa: %s\n",strlen(curr->data->clueSa) == 0 ? "EMPTY": curr->data->clueSa);
        printf("AssetType: %s\n",strlen(curr->data->assetType) == 0 ? "EMPTY": curr->data->assetType);
        printf("DeltaZ: %f\n",curr->data->deltaZ);
        printf("Distance: %f\n",curr->data->distance);
        printf("Grade1in: %f\n",curr->data->grade1in);
        printf("MccID: %d\n",curr->data->mccId);
        printf("MccIDint: %d\n",curr->data->mccIdInt);
        printf("R_Lmax: %f\n",curr->data->rLMax);
        printf("R_Lmin: %f\n",curr->data->rLMin);
        printf("SegSide: %s\n",strlen(curr->data->segSide) == 0 ? "EMPTY": curr->data->segSide);
        printf("StatusID: %d\n",curr->data->statusId);
        printf("StreetID: %d\n",curr->data->streetId);
        printf("StreetGroup: %d\n",curr->data->streetGroup);
        printf("StartLat: %f\n",curr->data->startLat);
        printf("StartLon: %f\n",curr->data->startLon);
        printf("EndLat: %f\n",curr->data->endLat);
        printf("EndLon: %f\n",curr->data->endLon);
        curr = curr->next;
        i++;
    }
}

int main(){

    Node* head = NULL; // Initialise linked list head,
    Node* tail = NULL; //   and tail.

    FILE* fp; // Create file pointer & open file
    fp = fopen("testdata_100.csv", "r"); // open file to be read

    fscanf(fp, "%*[^\n]\n"); // bypass first line (row headings)
    char buffer[MAX_RECORD]; // create buffer to hold each record that is iterated through

    memset(buffer, '\0', MAX_RECORD); // initialise buffer array

    // while loop allows for the csv rows to be iterated through, until the end
    while(fgets(buffer, MAX_RECORD, fp) != NULL){
        insert(&head, &tail, buffer); // create a node, fill it with record data & link it to linked list
    }

    fclose(fp); // close file
    printList(head); // TEST print

    // IGNORE (below code is temporary so the terminal doesn't close after printing list)
    char a;
    printf("\nPress ENTER to Exit");
    scanf("%c", &a);

    return 0;
}