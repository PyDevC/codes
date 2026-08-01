#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  int lengthOfLIS(std::vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    if (size < 2) {
      return size;
    }

    std::vector<int> answer(size, 1);
    for (int i{1}; i < size; ++i) {
      int len{};
      for (int j{}; j < size; ++j) {
        if (nums[i] < nums[j]) {
          answer[i] = std::max(nums[i], nums[j] + 1);
        }
      }
    }

    return *std::max_element(answer.begin(), answer.end());
  }
};

int main() {
  std::vector<int> nums = {};
  Solution sol;
  std::cout << sol.lengthOfLIS(nums);
  return 0;
}
