// Original (../gcd_two_number.cpp) was correct for positive inputs:
// recursive Euclid gcd(a, b) = gcd(b % a, a). Improvements:
//   1. Iterative form: same O(log min(a, b)), no call-stack use.
//   2. std::abs first: C++ '%' keeps the dividend's sign, so some negative
//      inputs leaked a negative result - e.g. gcd(-60, 45) returned -15.
//   3. gcd(0, x) == x falls out of the loop naturally; gcd(0, 0) == 0 by
//      convention.
#include <cstdlib>
#include <iostream>

class Solution {
public:
  int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
      int remainder = a % b;
      a = b;
      b = remainder;
    }
    return a;
  }
};

int main() {
  Solution sol;
  std::cout << sol.gcd(60, 36) << '\n';   // 12
  std::cout << sol.gcd(-60, 45) << '\n';  // 15 (original returned -15)
  std::cout << sol.gcd(0, 5) << '\n';     // 5
  return 0;
}
