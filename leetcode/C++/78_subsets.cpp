#include <iostream>
#include <vector>

class Solution {
  void backtrack(int start, std::vector<int> &path, std::vector<int> &nums,
                 std::vector<std::vector<int>> &result) {
    result.push_back(path);
    if (start >= nums.size())
      return;
    for (int i{start}; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      backtrack(i + 1, path, nums, result);
      path.pop_back();
    }
  }

public:
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    std::vector<std::vector<int>> result{};
    std::vector<int> path{};
    backtrack(0, path, nums, result);
    return result;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3};
  Solution sol;
  auto result = sol.subsets(nums);
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
