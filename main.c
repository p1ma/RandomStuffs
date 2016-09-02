#include <stdio.h>
#include <stdlib.h>
#include "mergeSort.h"

#define length 15

int main(int argc, char** argv){
  int array[length];
  initialization(array, length);
  print(array, length);
  sort(array, 0, length - 1);
  print(array, length);
  return EXIT_SUCCESS;
}
