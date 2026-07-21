#include <iostream>
#include <iterator>
#include <vector>

auto binary_search(std::vector<int> &arr, int target) {
  if (arr.empty())
    return arr.end();

  std::size_t high{arr.size()}, low{0};
  while (low < high) {
    auto mid_size = low + (high - low) / 2;
    auto mid = arr.begin() + mid_size;
    if (*mid == target) {
      return mid;
    } else if (*mid < target) {
      low = mid_size + 1;
    } else {
      high = mid_size;
    }
  }
  return arr.end();
}

int main() {
  std::vector<int> nums = {10, 20, 30, 40, 50, 60, 70, 80};
  int target = 10;
  auto it = binary_search(nums, target);
  auto value = *it;
  if (it != nums.end()) {
    std::cout << "target present in array at iterator "
              << std::distance(nums.begin(), it) << std::endl;
  } else {
    std::cout << "target not present in array" << std::endl;
  }
  return 0;
}
