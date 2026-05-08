#include <iostream>
#include <vector>
using namespace std;

// [1, 3, 5, 6]
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    int low = 0, high = nums.size() - 1;
    if (nums[low] > target)
      return 0;
    if (nums[high] < target)
      return high;
    int expected = 0;

    while (low < high) {
      int mid = (low + high) / 2;

      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        expected = mid + 1;
        low = mid + 1;
      } else {
        expected = mid;
        high = mid - 1;
      }
    }
    return expected;
  }
};

int main(void) {
  Solution sol;
  vector<int> nums = {1, 3, 5, 6};
  int output = sol.searchInsert(nums, 2);
  return output;
}
