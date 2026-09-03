// Original issues (../factorial.cpp):
//   1. factorial(0) returned 0 because `if (n < 2) return n;` echoes the
//      argument back. By definition 0! == 1.
//   2. Negative input silently returned the negative number itself.
//   3. int overflows at 13! (6227020800 > INT_MAX); widened to long long,
//      which holds factorials up to 20!. Beyond that a big-integer type is
//      required.
#include <iostream>

class Solution {
public:
  long long factorial(int n) {
    if (n < 0) {
      return -1; // undefined for negatives (could also throw)
    }
    long long fact{1};
    // n == 0 or n == 1 skips the loop and correctly returns 1.
    for (int i{2}; i <= n; ++i) {
      fact *= i;
    }
    return fact;
  }
};

int main() {
  Solution sol;
  std::cout << sol.factorial(0) << '\n';   // 1  (original printed 0)
  std::cout << sol.factorial(5) << '\n';   // 120
  std::cout << sol.factorial(20) << '\n';  // 2432902008176640000 (overflowed before)
  return 0;
}
