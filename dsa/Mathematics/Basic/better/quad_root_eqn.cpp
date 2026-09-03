// Original issues (../quad_root_eqn.cpp):
//   1. `b * b - 4 * a * c` was evaluated entirely in int. With coefficients
//      near the usual judge limit (~1e5), b*b alone reaches 1e10 >> INT_MAX:
//      signed overflow (UB) before the value ever reaches a double.
//      Widen to long long BEFORE multiplying.
//   2. Casting the double root straight to int truncates toward ZERO; the
//      common judge convention is FLOOR, which differs for negative
//      non-integer roots: trunc(-3.5) == -3 but floor(-3.5) == -4.
//   3. Typo "formlua"; also the discriminant variable name was misleading.
#include <cmath>
#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> quadraticRoots(int a, int b, int c) {
    // Quadratic formula; discriminant computed in 64-bit to avoid overflow.
    const long long discriminant = static_cast<long long>(b) * b - 4LL * a * c;
    if (discriminant < 0) {
      return {-1, -1}; // imaginary roots (some judges expect a single {-1})
    }

    const double sq = std::sqrt(static_cast<double>(discriminant));
    // Floor once, at the end, so both roots follow the floor convention.
    const int root1 = static_cast<int>(std::floor((-b + sq) / (2.0 * a)));
    const int root2 = static_cast<int>(std::floor((-b - sq) / (2.0 * a)));

    return {std::max(root1, root2), std::min(root1, root2)}; // larger first
  }
};

int main() {
  Solution sol;
  auto answer = sol.quadraticRoots(1, -2, 1);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n"; // [1, 1]

  answer = sol.quadraticRoots(4, 1, 8);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n";
  // [-1, -1] imaginary

  // Would overflow int in the original: disc = 200000^2 = 4e10 > INT_MAX.
  answer = sol.quadraticRoots(100000, 200000, 0);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n"; // [0, -2]
  return 0;
}
