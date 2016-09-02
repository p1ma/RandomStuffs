#include "mergeSort.h"

const int *sort(int *array, int start, int end){
  int k = 0;
  if(size(array) < 2){
    perror("Incorerct array's size !");
    exit(EXIT_FAILURE);
  }
  if(start < end){
    k = (start + end) / 2 ;
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
