#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> cache{};
    for (int i{}; i < nums.size(); ++i) {
      comp = target - nums[i];
      auto lookup = cache.find(nums[i]);
      if (lookup != cache.end()) {
        return {lookup->second, i};
      }
      cache.insert({comp, i});
    }
    return {};
  }
};

int main() {
  Solution sol{};
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;
  vector<int> answer = sol.twoSum(nums, target);
  if (!answer.empty()) {
    cout << answer[0] << ", " << answer[1];
  }
  return 0;
}
