#ifndef _MERGE_SHOT_
#define _MERGE_SHOT_

#include <time.h> // for random
#include <stdlib.h> // for random
#include <stdio.h> // for printf

void sort(int *array, int start, int end);

void merge(int *array, int start, int mid, int end);

void initialization(int *array, const int length);

void print(int *array, int start, int end);

int size(int *array);

#endif // _MERGE_SHOT_
