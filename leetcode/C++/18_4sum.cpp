#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    int n = nums.size();
    if (n < 4) {
      return {};
    }
    vector<vector<int>> result{};
    std::sort(nums.begin(), nums.end());

    for (int i{}; i < n - 3; ++i) {
      for (int j{i + 1}; j < n - 2; ++j) {
        int left{j + 1}, right{n - 1};
        while (left < right) {
          long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
          if (sum == target) {
            result.push_back({nums[i], nums[j], nums[left], nums[right]});
            while (left < right && nums[left] == nums[left + 1])
              ++left;
            while (left < right && nums[right] == nums[right - 1])
              --right;
            ++left;
            --right;
          } else if (sum > target) {
            --right;
          } else {
            ++left;
          }
        }
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {1, 0, -1, 0, -2, 2};
  int target = 0;
  Solution sol;
  auto answer = sol.fourSum(nums, target);

  std::cout << "[ ";
  for (auto ans : answer) {
    std::cout << "[ ";
    for (auto a : ans) {
      std::cout << a << ", ";
    }
    std::cout << "\b\b ], ";
  }
  std::cout << "\b\b ]" << std::endl;
  return 0;
}
