#include <stdio.h>

void two_sum(int *nums, int size, int target, int *answer) {
  for (int i = 0; i < size; ++i) {
    for (int j = 1; j < size; ++j) {
      if (i != j && target == nums[i] + nums[j]) {
        answer[0] = i;
        answer[1] = j;
      }
    }
  }
}

int main(void) {
  int nums[] = {2, 7, 11, 15};
  int target = 9;
  int size = sizeof(nums) / sizeof(int);
  int answer[2] = {};
  two_sum(nums, size, target, answer);
  printf("%d, %d", *answer, *(answer + 1));
}
