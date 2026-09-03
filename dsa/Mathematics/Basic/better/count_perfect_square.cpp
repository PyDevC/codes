// Original issues (../count_perfect_square.cpp):
//   1. Logic (count k with k*k < n, i.e. ceil(sqrt(n)) - 1) was right, but the
//      result relied on implicit double->int truncation in the return of an
//      int function - silent narrowing conversion.
//   2. Pure std::sqrt is fragile near 2^31: one ulp of fp error flips a
//      perfect-square boundary and miscounts by one. Here fp sqrt only gives
//      an initial guess; the boundary is settled with exact integer math.
#include <cmath>
#include <iostream>

class Solution {
public:
  int countSquares(int n) {
    if (n <= 1) {
      return 0; // no positive k satisfies k*k < 1; also guards n - 1 below
    }

    const long long target = n - 1; // largest value k*k is allowed to reach

    long long r = static_cast<long long>(std::sqrt(static_cast<double>(target)));
    while (r * r > target) {             // fp guess overshot -> step down
      --r;
    }
    while ((r + 1) * (r + 1) <= target) { // fp guess undershot -> step up
      ++r;
    }
    return static_cast<int>(r);           // explicit: no silent narrowing
  }
};

int main() {
  Solution sol;
  std::cout << sol.countSquares(234) << '\n';        // 15 (15^2=225 < 234)
  std::cout << sol.countSquares(225) << '\n';        // 14 (strictly below)
  std::cout << sol.countSquares(226) << '\n';        // 15 (225 counts here)
  std::cout << sol.countSquares(2147395600) << '\n'; // 46339, edge region
  return 0;
}
