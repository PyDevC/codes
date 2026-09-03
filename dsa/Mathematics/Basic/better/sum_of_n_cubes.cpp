// Original (../sum_of_n_cubes.cpp) used the right identity,
// 1^3 + 2^3 + ... + n^3 == (n(n+1)/2)^2, but overflowed int quickly:
//   * n * (n + 1) exceeds INT_MAX once n >= 46341,
//   * the final square exceeds INT_MAX once n >= 481.
// Widening to long long moves the wrap-around to n >= ~77937 (where the
// squared triangular number passes LLONG_MAX); beyond that use __int128 or a
// big-integer type. The division by 2 is exact because n(n+1) is always even.
#include <iostream>

class Solution {
public:
  long long sumOfSeries(long long n) {
    const long long triangular = n * (n + 1) / 2; // sum 1..n
    return triangular * triangular;               // sum of cubes identity
  }
};

int main() {
  Solution sol;
  std::cout << sol.sumOfSeries(7) << '\n';      // 784 = 28^2
  std::cout << sol.sumOfSeries(481) << '\n';    // already overflowed int in original
  std::cout << sol.sumOfSeries(10000) << '\n';  // 2500500025000000 fits 64-bit
  return 0;
}
