#include <vector>

using namespace std;
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    for (int i = 0, e = nums.size(); i != e; ++i) {
      if (nums[i] >= target) {
        return i;
      }
    }
    return nums.size();
  }
};
