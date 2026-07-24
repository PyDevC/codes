#include <iostream>
#include <vector>

class Solution {
public:
  int maxSubArray(std::vector<int> &nums) {
    int bestSum{nums[0]};
    int currSum{};
    for (auto n : nums) {
      currSum = std::max(currSum + n, n);
      bestSum = std::max(currSum, bestSum);
    }
    return bestSum;
  }
};

int main() {
  std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  Solution sol;
  std::cout << sol.maxSubArray(nums);
  return 0;
}
