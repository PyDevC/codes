#include <stdlib.h>

int main(void) {
  int size = 2;
  int ***array2 = new int **[size];
  for (int i = 0; i < size; i++) {
    array2[i] = new int *[size];
    for (int j = 0; j < size; j++) {
      array2[i][j] = new int[size];
    }
  }
  delete[] array2;

  int ***array3 = new int **[size];
  for (int i = 0; i < size; i++) {
    array3[i] = new int *[size];
    for (int j = 0; j < size; j++) {
      array3[i][j] = new int[size];
    }
  }
  return 0;
}
