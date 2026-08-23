#include "helper.hpp"

class Solution {
public:
  std::vector<std::vector<int>> getPairs(std::vector<int> &arr) {
    std::vector<std::vector<int>> result{};
    return result;
  }
};

int main() {

  std::vector<int> arr{};
  Solution sol;
  auto vec = sol.getPairs(arr);

  std::cout << "[" << std::endl;
  for (auto &v : vec) {
    printVector(v);
  }
  std::cout << "]" << std::endl;
  return 0;
}
