#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> resultArray(std::vector<int> &nums) {
    std::vector<int> arr1 = {nums[0]};
    std::vector<int> arr2 = {nums[1]};

    int numsSize = static_cast<int>(nums.size());
    for (int i{2}; i < numsSize; ++i) {
      if (arr1.back() > arr2.back()) {
        arr1.push_back(nums[i]);
      } else {
        arr2.push_back(nums[i]);
      }
    }

    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    return arr1;
  }
};

int main() {
  std::vector<int> nums = {6,  10, 11, 20, 24, 27, 29, 34, 46, 48, 51, 53, 59,
                           63, 66, 68, 70, 74, 77, 79, 86, 88, 93, 95, 98};
  Solution sol;
  auto result = sol.resultArray(nums);

  std::cout << "[";
  for (auto e : result) {
    std::cout << e << ", ";
  }
  std::cout << "]";
  return 0;
}
