#include <iostream>
#include <vector>

class Solution {
  void backtrack(int i, std::vector<int> &nums,
                 std::vector<std::vector<int>> &result) {
    if (i == nums.size()) {
      result.push_back(nums);
      return;
    }

    for (int j{i}; j < nums.size(); ++j) {
      std::swap(nums[i], nums[j]);
      backtrack(i + 1, nums, result);
      std::swap(nums[i], nums[j]);
    }
  }

public:
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> result{};
    backtrack(0, nums, result);
    return result;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3};
  Solution sol;
  auto result = sol.permute(nums);
  std::cout << "[";
  for (auto res : result) {
    std::cout << "[";
    for (auto r : res) {
      std::cout << r << ", ";
    }
    std::cout << "], ";
  }
  std::cout << "]";
  return 0;
}
