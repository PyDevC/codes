#include <vector>
using namespace std;

class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    if (nums.empty())
      return 0;

    int move = 0;
    int size = nums.size();
    for (int i = 1; i < size; ++i) {
      if (nums[move] != nums[i]) {
        nums[move] = nums[i];
        move++;
      }
    }

    return move + 1;
  }
};
