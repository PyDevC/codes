#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxSubarrayLength(vector<int> &nums, int k) {
    if (nums.empty())
      return 0;

    int result{};

    unordered_map<int, int> freq{};
    int left{}, right{};

    while (left <= right && right < nums.size()) {
      freq[nums[right]]++;

      // shrink window
      while (freq[nums[right]] > k) {
        freq[nums[left]]--;
        left++;
      }

      result = std::max(result, (right - left + 1));

      // expand window
      right++;
    }

    return result;
  }
};

int main() {
  Solution sol{};
  std::vector<int> nums = {5, 5, 5, 5, 5, 5};
  int k = 4;
  std::cout << sol.maxSubarrayLength(nums, k);
  return 0;
}
