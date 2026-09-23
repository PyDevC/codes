#include <bits/stdc++.h>
using namespace std;

int recursive(int l, int r, std::vector<int> &nums, vector<vector<int>> &dp) {
  if (l + 1 == r) {
    return 0;
  }

  if (dp[l][r] != -1) {
    return dp[l][r];
  }

  int ans = 1e9;
  for (int p{l + 1}; p <= (r - 1); ++p) {
    ans = std::min(ans, (nums[r] - nums[l]) + recursive(l, p, nums, dp) +
                            recursive(p, r, nums, dp));
  }
  return dp[l][r] = ans;
}

int lowestCostBreakingSticks(std::vector<int> &nums) {
  int n = nums.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));
  return recursive(0, n, nums, dp);
}

int main() {
  std::vector<int> nums{0, 1, 2, 3, 5, 23};
  cout << lowestCostBreakingSticks(nums) << endl;
  return 0;
}
