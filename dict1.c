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
}Record;
typedef struct Node{
    Record* data;
    struct Node* next;

}Node;

Record* importRec(char* stringRec){
    Record* structRec = malloc(sizeof(Record));
    int right, left=0, i=0, comma=0;
    char tmpField[MAX_FIELD];
    memset(tmpField, '\0', MAX_FIELD);
    for (right = 0; *stringRec != '\0'; stringRec++, right++){
        if (*stringRec == ','){

            switch (comma){
                case 0:

            }


//            char* address = calloc(right, sizeof(char));
//            strncpy(address, tmpField + left, right - left);
//            structRec->address = address;
//            memset(tmpField, '\0', right-left);
//            left = right;
//            i = 0; // reset tmpField iterator
//            continue;
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
    char buffer[200] = {"27665,Palmerston Street between Rathdowne Street and Drummond Street,Carlton,Road Footway,3.21"};
//    fgets(buffer,MAX_RECORD,fPtr);
    insert(&head, buffer);

}