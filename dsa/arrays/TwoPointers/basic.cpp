#include <cassert>
#include "helper.hpp"

std::pair<int, int> getPairForTargetSum(const std::vector<int> &nums,
                                        const int target) {
  int left{}, right{static_cast<int>(nums.size()) - 1};

  while (left < right) {
    auto pairSum = nums[left] + nums[right];
    if (pairSum == target) {
      return {left, right};
    } else if (pairSum > target) {
      --right;
    } else {
      ++left;
    }
  }

  return {};
}

template <typename T>
void checkPair(const std::pair<T, T> &pair1, const std::pair<T, T> pair2) {
  assert(pair1 == pair2);
}

int main() {
  std::vector<int> vec{10, 20, 35, 50};
  printVector(vec);
  const int target{70};
  auto targetPair = getPairForTargetSum(vec, target);
  checkPair(targetPair, {1, 3});
  return 0;
}
