// Original issues (../lcm_gcd.cpp):
//   The trial-division factorisation was buggy:
//   1. LCM loop used `i < min`, so it never ran when the smaller operand is
//      small: LCM(2, 2) returned 4 and LCM(6, 3) returned 18.
//   2. GCD advanced `i` even after a successful division, missing repeated
//      prime factors: GCD(27, 9) returned 3 instead of 9.
//   3. Both loops are O(n); Euclid's algorithm is O(log min(a, b)) and needs
//      no factorisation at all. LCM then follows from lcm = a / gcd * b
//      (divide FIRST - keeps the intermediate small and delays overflow).
//   4. std::min/std::max were relied on transitively; <algorithm> is now
//      included explicitly (kept for the driver below).
//   Production code can simply use std::gcd / std::lcm from <numeric> (C++17).
#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  static int GCD(int a, int b) {
    while (b != 0) {
      int remainder = a % b;
      a = b;
      b = remainder;
    }
    return a; // gcd(0, 0) == 0 by convention
  }

  static int LCM(int a, int b) {
    const int g = GCD(a, b);
    return g == 0 ? 0 : (a / g) * b;
  }

public:
  std::vector<int> lcmAndGcd(int a, int b) {
    return {LCM(a, b), GCD(a, b)};
  }
};

int main() {
  Solution sol;
  auto answer = sol.lcmAndGcd(99, 121);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n"; // [1089, 11]
  answer = sol.lcmAndGcd(2, 2);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n"; // [2, 2] (was [4, 2])
  answer = sol.lcmAndGcd(27, 9);
  std::cout << "[" << answer[0] << ", " << answer[1] << "]\n"; // [27, 9] (gcd was 3)
  return 0;
}
