#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int longestSubsequence(vector<int> &nums) {
    if (nums.size() == 1) {
      return nums[0] == 0 ? 0 : 1;
    }

    int x = std::reduce(nums.begin(), nums.end(), 0, std::bit_xor<>{});
    int n = static_cast<int>(nums.size());

    if (x != 0) {
      return n;
    }

    bool nonZero = false;
    for (auto num : nums) {
      if (num != 0) {
        nonZero = true;
        break;
      }
    }

    if (!nonZero)
      return 0;

    return n - 1;
  }
};
