#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    int size = nums.size();
    if (size < 2)
      return vector<int>();

    unordered_map<int, int> indexMap;
    for (int i = 0; i < size; i++) {
      int comp = target - nums[i];
      auto it = indexMap.find(comp);
      if (it != indexMap.end()) {
        return {it->second, i};
      } else {
        indexMap[nums[i]] = i;
      }
    }
    return {};
  }
};

// [1,2,3,4,5,6,7,8,9,0]
// [8,7,6,5,4,3,2,1,0,-1]
// x
