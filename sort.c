#include "sort.h"

int sort(Record** array, int left, int right){
    int i = left;
    int j = right-1;
    double pivot = array[right]->grade1in;

    while (i < j){
        while (i < right && array[i]->grade1in < pivot){
            i++;
        }
        while (j > left && array[j]->grade1in >= pivot){
            j--;
        }
        if (i < j){
            Record* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    if (array[i]->grade1in > pivot){
        Record* temp = array[i];
        array[i] = array[right];
        array[right] = temp;
    }
    return i;
}

void quicksort(Record** array, int left, int right){
    if (left < right){
        int index = sort(array, left, right);
        quicksort(array, left, index - 1);
        quicksort(array, index + 1, right);}}
