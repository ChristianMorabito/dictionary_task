#include "sort.h"


int sort(Record** array, int left, int right){
    int i = left;
    int j = right-1;
    double pivot = (*(array + right))->grade1in;

    while (i < j){
        while (i < right && (*(array + i))->grade1in < pivot){
            i++;
        }
        while (j > left && (*(array + j))->grade1in >= pivot){
            j--;
        }
        if (i < j){
            double temp = (*(array + i))->grade1in;
            (*(array + i))->grade1in = (*(array + j))->grade1in;
            (*(array + j))->grade1in = temp;
        }
    }
    if ((*(array + i))->grade1in > pivot){
        double temp = (*(array + i))->grade1in;
        (*(array + i))->grade1in = (*(array + right))->grade1in;
        (*(array + right))->grade1in = temp;
    }
    return i;
}

void divide(Record** array, int left, int right){
    if (left < right){
        int index = sort(array, left, right);
        divide(array, left, index - 1);
        divide(array, index + 1, right);}}
