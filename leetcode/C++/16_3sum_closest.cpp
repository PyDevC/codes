#include <bits/stdc++.h>
using namespace std;

class Solution {
  inline bool isClosest(int target, int closestVal, int currVal) {
    return std::abs(target - closestVal) > std::abs(target - currVal);
  }

public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    int n = static_cast<int>(nums.size());
    if (n == 3) {
      return nums[0] + nums[1] + nums[2];
    }

    std::sort(nums.begin(), nums.end());
    int closest = nums[0] + nums[1] + nums[2];
    for (int i{}; i < n; ++i) {
      int left{}, right{n - 1};
      while (left < right) {
        if (i == left || i == right || left == right) {
          break;
        }
        int sum = nums[i] + nums[left] + nums[right];
        if (isClosest(target, closest, sum)) {
          closest = sum;
        } else {
          if (sum == target) {
            return sum;
          } else if (sum > target) {
            --right;
          } else {
            ++left;
          }
        }
      }
    }
    return closest;
  }
};

int main() {
  std::vector<int> nums = {1, 1, 1, 0};
  int target = 100;
  Solution sol;
  std::cout << sol.threeSumClosest(nums, target) << std::endl;
  return 0;
}
