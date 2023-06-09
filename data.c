#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "data.h"
#include "linked_list.h"

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
        printf("Error: Out of memory. Exiting...\n");
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
            puts("Error when creating Record");
            exit(-1);
    }
}

Record* importRec(char* stringRec){
    Record* structRec = malloc(sizeof(Record));
    if (structRec == NULL){
        puts("Memory Allocation Error. Exiting...");
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

bool outputText(void* data, FILE* fpWrite, void(outputStructure)(void*, FILE*, char*)) {
    char buffer[MAX_FIELD];
    memset(buffer, '\0', MAX_FIELD);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        return false;
    }
    outputStructure(data, fpWrite, buffer);
    return true;
}

void outputDynamicList(void* voidData, FILE* fpWrite, char* buffer){
    *buffer == '\n' ? fputs("0.00\n", fpWrite) : fputs(buffer, fpWrite);
    buffer[strlen(buffer) - 1] = '\0'; // This line is to overwrite the trailing '\n'.

    // CREATE DOUBLE
    double input = createDouble(buffer);


    Record* preCurr = NULL;
    Record* postCurr = NULL;
    Record* result = NULL;

    traverseDynamicList((Record**)voidData, &preCurr, &postCurr, &result, input);

    char* stdOut = "";

    if (!result){
        if (!preCurr){
            stdOut = ": OUT OF RANGE. Min. listed number is";
            result = postCurr;
        }
        else if (!postCurr){
            stdOut = ": OUT OF RANGE. Max. listed number is";
            result = preCurr;
        }
        else {
            result = findDiff(input - preCurr->grade1in, postCurr->grade1in - input, preCurr, postCurr);
        }
    }

    printf("%.1f%s --> %.1f\n", input, stdOut, result->grade1in); // STDOUT PRINT STATEMENT
    writeData(fpWrite, result);

}

void traverseDynamicList(Record** curr, Record** preCurr, Record** postCurr, Record** result, double input){

    while (*curr){
        if ((*curr)->grade1in < input){
            *preCurr = *curr;
        }
        else if ((*curr)->grade1in == input){
            *result = *curr;
            break;
        }
        else {
            *postCurr = *curr;
            break;
        }
        curr++;
    }

}

Record* findDiff(double preDiff, double postDiff, Record* preCurr, Record* postCurr){
    Record* result = NULL;

    if (preDiff <= postDiff){
        result = preCurr;
    }
    else{
        result = postCurr;
    }
    return result;


}

void outputLinkedList(void* voidData, FILE* fpWrite, char* buffer){

    int i = 0;
    int value;

    *buffer == '\n' ? fputs("(unfilled address)\n", fpWrite) : fputs(buffer, fpWrite);
    buffer[strlen(buffer) - 1] = '\0'; // This line is to overwrite the trailing '\n'.

    LinkedList* linkedList = (LinkedList* )voidData;
    Node* curr = linkedList->head;

    while (curr){
        Record* data = curr->data;
        value = strcmp(buffer, data->address);
        if (value == 0) {
            writeData(fpWrite, curr->data);
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


void writeData(FILE* fpWrite, Record* data){
    fprintf(fpWrite, "-->");
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