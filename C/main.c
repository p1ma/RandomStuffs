#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "mergeSort.h"

#define length 50000

// chronometer
time_t begin, end;


void testMergeSort(){
  int array[length];
  initialization(array, length); // initialize array with 'length' randoms values
  printf("Initial array : \n");
  print(array, 0, length);
  printf("\n"); 
  begin = time(0); // start chronometer
  sort(array, 0, length - 1); // start merge sort on array
  end = time(0); // end chronometer
  printf("Final array : \n");
  print(array, 0, length);
  printf("\n");
  printf("Execution time :  %.2f s\n", difftime(end,begin));
}

// MAIN
int main(int argc, char* argv[]){
  testMergeSort();
  return EXIT_SUCCESS;
}
