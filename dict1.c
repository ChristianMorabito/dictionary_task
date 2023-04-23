#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FIELD 128
#define MAX_RECORD 512
#define FIELD_N 19

typedef struct{
    int fPathId;
    char* address;
    char* clueSa;
    char* assetType;
    double deltaZ;
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

char* createString(int right, int left, char* tmpField){
    char* string = calloc(strlen(tmpField), sizeof(char));
    strncpy(string, tmpField, (right - left));
    return string;

}

Record* importRec(char* stringRec){
    Record* structRec = malloc(sizeof(Record));
    int right, left=0;
    int i=0, comma=1;
    char tmpField[MAX_FIELD];
    memset(tmpField, '\0', MAX_FIELD);
    for (right=0; *stringRec != '\0'; right++, stringRec++){
        if (*stringRec == ','){

            switch (comma){
                case 1:
                    structRec->fPathId = atoi(tmpField);
                    break;
                case 2:
                    structRec->address = createString(right, left, tmpField);
                    break;
                case 3:
                    structRec->clueSa = createString(right, left, tmpField);
                    break;

                default:
                    printf("Error");
            }
            memset(tmpField, '\0', (right-left)-1);
            left = right;
            i = 0; // reset tmpField iterator
            comma++;
            continue;
        }
        tmpField[i] = *stringRec;
        i++;

    }
    return structRec;
}
void insert(Node** head, char* strRec){
    // create struct Record
    Record* structRec = importRec(strRec);
    // create struct Node
    Node* newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = structRec;

    if (!*head){
        *head = newNode;
        return;
    }
    // linked list pointer
    Node* curr = *head;
}

int main(){
    Node* head = NULL;
//    FILE* fPtr = fopen("prac.csv", "r");
    char buffer[MAX_RECORD] = {"453452433,bob,carlton Road Footway,3.21"};
//27,Palmerston Street between Rathdowne Street and Drummond Street,Carlton
//    fgets(buffer,MAX_RECORD,fPtr);
    insert(&head, buffer);

}