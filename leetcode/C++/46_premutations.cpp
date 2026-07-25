#include <iostream>
#include <vector>

class Solution {
  void backtrack(std::vector<bool> &used, std::vector<int> &path,
                 std::vector<int> &nums,
                 std::vector<std::vector<int>> &result) {
    if (path.size() == nums.size()) {
      result.push_back(path);
      return;
    }
    for (int i{}; i < nums.size(); ++i) {
      if (!used[i]) {
        path.push_back(nums[i]);
        used[i] = true;
        backtrack(used, path, nums, result);
        used[i] = false;
        path.pop_back();
      }
    }
  }

public:
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> result{};
    std::vector<int> path{};
    std::vector<bool> used(nums.size(), false);
    backtrack(used, path, nums, result);
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
