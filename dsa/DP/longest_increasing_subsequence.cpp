#include <bits/stdc++.h>
using namespace std;

int recursive_lis(int idx, std::vector<int> &nums, std::vector<int> &dp) {
  if (idx < 0)
    return 0;

  if (dp[idx] != -1) {
    return dp[idx];
  }

  int ans = 1;
  for (int prev{}; prev < idx; ++prev) {
    if (nums[prev] <= nums[idx]) {
      ans = std::max(ans, 1 + recursive_lis(prev, nums, dp));
    }
  }

  dp[idx] = ans;
  return ans;
}

int lis(vector<int> nums) {
  if (nums.size() < 2) {
    return nums.size();
  }
  vector<int> dp(nums.size(), -1);

  int best{};
  for (int i{}; i < nums.size(); ++i) {
    best = max(best, recursive_lis(nums.size() - 1, nums, dp));
  }
  return best;
}

int main() {
  cout << lis({23, 23, 234, 1,  5,   2342, 234, 234, 234, 23, 234, 23, 23,
               23, 23, 23,  23, 234, 2,    6,   2,   3,   6,  7,   7,  76})
       << endl;
  return 0;
}
