#include <stdio.h>

void linear_search(int arr[], int size, int search) {
  int i;
  for (i = 0; i < size; i++) {
    if (arr[i] == search) {
      printf("Element was found at index %d", arr[i]);
      break;
    }
  }
  if (i == size) {
    printf("Element not found");
  }
}

int main(void) {
  int search;
  int arr[] = {12, 234, 34, 89, 45, 55, 4, 6, 45, 55};
  int i;
  scanf("%d", &search);
  linear_search(arr, 10, search);
  return 0;
}
