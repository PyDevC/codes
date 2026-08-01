#include <iostream>
#include <numeric>
#include <vector>

class Solution {
public:
  bool canParition(std::vector<int> &nums) {
    auto sum = std::accumulate(nums.begin(), nums.end(), 0);
    auto n = nums.size();
    if (sum % 2 != 0) {
      return false;
    }
    sum = sum / 2;
    std::vector<std::vector<int>> dp(n, std::vector<int>(sum + 1, false));
    for (int i{}; i <= n; ++i) {
      dp[i][0] = true;
    }

    for (int i{1}; i <= n; ++i) {
      for (int j{1}; j <= sum; ++j) {
        if (j < nums[i - 1]) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        }
      }
    }
    return dp[n][sum];
  }
};

int main() {
  std::vector<int> nums = {};
  Solution sol;
  std::cout << sol.canParition(nums);
  return 0;
}
