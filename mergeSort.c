#include "mergeSort.h"

void sort(int *array, int start, int end){
  if(start < end){
    int k = 0;
    k = (start + (end - 1 )) / 2 ;
    sort(array, start, k);
    sort(array, k + 1, end);
    merge(array, start, k, end);
  }
}

void merge(int *array, int start, int mid, int end){
  // assign left and right size
  int l = mid - start + 1 ; // left side
  int r = end - mid;

  // create 2 temporaries arrays
  int left[l];
  int right[r];

  // copy values from array to left and right
  for(int i = 0 ; i < l ; i++){
    left[i] = array[start + i];
  }
  for(int i = 0 ; i < r ; i++){
    right[i] = array[mid + 1 + i];
  }
  
  int i, j, k;
  i = 0;
  j = 0;
  k = start;
  while(i < l && j < r){
    if(left[i] <= right[j]){
      array[k] = left[i];
      i++;
    }else{
      array[k] = right[j];
      j++;
    }
    k++;
  }

  // copy remaining elements
  while(i < l){
    array[k] = left[i];
    i++;
    k++;
  }

  while(j < r){
    array[k] = right[j];
    j++;
    k++;
    }
}

void initialization(int *array, const int length){
  srand((unsigned)time(NULL));
  for(int i = 0 ; i < length ; i++){
    array[i] = rand() % 100;
  }
  return;
}

void print(int *array, const int length){
  for(int i = 0 ; i < length; i++){
    printf("[%d]",array[i]);
  }
  printf("\n");
  return;
}

int size(int *array){
  int counter = 0;
  while(*array){
    array++;
    counter++;
  }
  return counter;
}
