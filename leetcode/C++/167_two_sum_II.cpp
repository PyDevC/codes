#include <iostream>
#include <vector>
class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &numbers, int target) {
    if (numbers.empty()) {
      return {};
    }

    int left{}, right{(int)numbers.size() - 1};
    while (left < right) {
      int sum = numbers[left] + numbers[right];
      if (sum == target) {
        return {left + 1, right + 1};
      } else if (sum < target) {
        ++left;
      } else {
        --right;
      }
    }
    return {};
  }
};

int main() {
  std::vector<int> numbers = {2, 7, 11, 15};
  int target{9};
  Solution sol;
  auto answer = sol.twoSum(numbers, target);
  if (!answer.empty()) {
    std::cout << answer[0] << ", " << answer[1] << std::endl;
  }
  return 0;
}
