#include <stdio.h>

void binary_search(int arr[], int search) {
  int low, high, mid;
  low = 0;
  high = 9;
  while (high >= low) {
    mid = low + (high - low) / 2;
    if (arr[mid] == search) {
      printf("Element found at index %d", mid);
      break;
    } else if (arr[mid] > search) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
}

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int search;
  scanf("%d", &search);
  binary_search(arr, search);
  return 0;
}
