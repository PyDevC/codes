#include <iostream>
#include <vector>

class Solution {
  void backtrace(int i, std::vector<int> &nums, std::vector<int> &path,
                 std::vector<std::vector<int>> &results) {
    if (i == nums.size()) {
      results.push_back(path);
      return;
    }

    // take
    path.push_back(nums[i]);
    backtrace(i + 1, nums, path, results);

    // skip
    path.pop_back();
    backtrace(i + 1, nums, path, results);
  }

public:
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    std::vector<std::vector<int>> result{};
    std::vector<int> path{};
    backtrace(0, nums, path, result);
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
