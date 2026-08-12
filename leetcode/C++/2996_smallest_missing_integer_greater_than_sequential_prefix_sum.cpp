#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int missingInteger(vector<int> &nums) {
    int prefixSum = nums[0];
    for (int i{1}; i < static_cast<int>(nums.size()); ++i) {
      if (nums[i] == nums[i - 1] + 1) {
        prefixSum += nums[i];
      } else {
        break;
      }
    }

    unordered_set<int> numSet(nums.begin(), nums.end());
    while (numSet.count(prefixSum)) {
      prefixSum++;
    }

    return prefixSum;
  }
};

int main() {
  Solution sol{};
  std::vector<int> nums = {5, 6, 7, 5, 5, 5};
  std::cout << sol.missingInteger(nums);
  return 0;
}
