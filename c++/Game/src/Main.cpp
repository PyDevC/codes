#include <iostream>
#include <stdlib.h>

int main(void) {
  int size = 2000;
  int *array2 = new int[size * size * size];
  for (int z = 0; z < size; z++) {
    for (int y = 0; y < size; y++) {
      for (int x = 0; x < size; x++) {
        array2[x + y * size + z * size * size] = x * y;
      }
    }
  }

  delete[] array2;
  return 0;
}
