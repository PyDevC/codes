#include "print_functions.h"

void bubble_sort(std::vector<int> &arr) {
  int temp{};
  for (int i{}; i < arr.size(); ++i) {
    for (int j{}; j < arr.size(); ++j) {
      if (arr[i] < arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int main() {
  std::vector<int> nums = {23423, 23, 231, 1, 2, 4, 6, 23, 4};
  std::cout << nums << std::endl;
  bubble_sort(nums);
  std::cout << nums << std::endl;
  return 0;
}
