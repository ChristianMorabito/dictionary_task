#ifndef DATA_H
#define DATA_H
#define MAX_FIELD 128

#include <stdbool.h>
#include <stdio.h>
#include "linked_list.h"

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

int createInt(char* tmpField);

double createDouble(char* tmpField);

char* createString(int right, int left, char* tmpField);

void fillRecordStruct(Record* structRec, int comma, char* tmpField, int right, int left);

Record* importRec(char* stringRec);

void freeRecordData(void* voidData);

void writeData(FILE* fpWrite, Record* data);

bool outputText(void* data, FILE* fpWrite, void(outputStructure)(void*, FILE*, char*));

void outputDynamicList(void* voidData, FILE* fpWrite, char* buffer);

Record* findDiff(double preDiff, double postDiff, Record* preCurr, Record* postCurr);

void traverseDynamicList(Record** curr, Record** preCurr, Record** postCurr, Record** result, double input);

void outputLinkedList(void* data, FILE* fpWrite, char* buffer);


#endif // DATA_H