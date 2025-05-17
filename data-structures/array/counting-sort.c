#include <stdio.h>

void counting_sort(int arr[], int size, int k) {
  int i;
  int count[k];
  int newsorted[size];

  for (i = 0; i < k; i++) {
    count[i] = 0;
  }

  for (i = 0; i < size; i++) {
    count[arr[i]-1]++;
  }

  for (i = 0; i < k; i++) {
    printf("%d ", count[i]);
  }
}

int main(void) {
  int arr[] = {1, 4, 4, 2, 3, 5, 7, 8, 8, 6};
  int k = 8;
  int size = 10;
  counting_sort(arr, size, k);
  return 0;
}
