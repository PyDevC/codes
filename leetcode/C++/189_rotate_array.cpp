#include <algorithm>
#include <vector>

class Solution {
public:
  void rotate(std::vector<int> &nums, int k) {
    int n = nums.size();
    k %= n;
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin() + k);
    std::reverse(nums.begin() + k, nums.end());
  }
};

int main() {
  std::vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
  Solution sol;
  sol.rotate(arr1, 3);
}
