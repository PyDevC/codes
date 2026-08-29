#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::set<std::vector<int>> triplets{};
    if (nums.size() < 3) {
      return std::vector<std::vector<int>>(triplets.begin(), triplets.end());
    }

    std::unordered_map<int, int> cache{};
    for (int i{}; i < nums.size(); ++i) {
      int target = -nums[i];
      std::vector<int> tri(3);
      for (int j{i + 1}; j < nums.size(); ++j) {
        int comp = target - nums[j];
        auto lookup = cache.find(comp);
        if (lookup != cache.end()) {
          if (lookup->second == i) {
            tri[0] = nums[i], tri[1] = comp, tri[2] = nums[j];
            std::sort(tri.begin(), tri.end());
            triplets.insert(tri);
          }
        }
        cache[nums[j]] = i;
      }
      cache.clear();
    }
    return std::vector<std::vector<int>>(triplets.begin(), triplets.end());
  }
};

int main() {
  std::vector<int> question = {-1, 0, 1, 2, -1, -4};
  std::vector<std::vector<int>> answer{};
  Solution sol;
  answer = sol.threeSum(question);

  std::cout << "[ ";
  for (auto ans : answer) {
    std::cout << "[ ";
    for (auto a : ans) {
      std::cout << a << ", ";
    }
    std::cout << "\b\b ], ";
  }
  std::cout << "\b\b ]" << std::endl;

  return 0;
}
