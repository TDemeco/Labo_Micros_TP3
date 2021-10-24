#include "array_compare.h"

bool compareArrays(uint8_t a[], uint8_t b[], int size_of_arrays) {
  int i;
  for(i = 1; i < size_of_arrays; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}