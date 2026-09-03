#include <cmath>
#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> quadraticRoots(int a, int b, int c) {
    // Quadratic formlua
    double rootConst = ((b * b) - (4 * a * c));
    if (rootConst < 0) {
      return {-1, -1};
    }

    int root1 = (-b + std::sqrt(rootConst)) / (2 * a);
    int root2 = (-b - std::sqrt(rootConst)) / (2 * a);

    return {std::max(root1, root2), std::min(root1, root2)};
  }
};

int main() {
  Solution sol;
  auto answer = sol.quadraticRoots(1, -2, 1);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]" << std::endl;

  answer = sol.quadraticRoots(4, 1, 8);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]" << std::endl;
  return 0;
}
