#include <stdio.h>

void bubble_sort(int arr[], int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        arr[j] = arr[j] ^ arr[j + 1];
        arr[j + 1] = arr[j] ^ arr[j + 1];
        arr[j] = arr[j] ^ arr[j + 1];
      }
    }
  }
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
}

int main(void) {
  int i;
  int arr[] = {1, 4, 4, 2, 3, 5, 7, 8, 8, 6};
  int size = 10;
  bubble_sort(arr, size);
  return 0;
}
