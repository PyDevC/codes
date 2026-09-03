// Original (../reverse_digits.cpp) was correct for positive inputs whose
// reversal also fits in int, but:
//   1. Contained dead variables (`sum`, `remainder`) that were never used.
//   2. Silently returned 0 for negative n (loop condition `n > 0`); the
//      conventional behaviour preserves the sign: reverse(-456) == -654.
//   3. Reversing e.g. 1999999999 overflows int (UB). Widening the accumulator
//      to long long makes the arithmetic safe; callers that must detect
//      32-bit overflow can range-check the returned value themselves.
#include <iostream>

class Solution {
public:
  long long reverseDigits(int n) {
    const bool negative = n < 0;
    // Negate through long long: -INT_MIN is not representable in int.
    long long value =
        negative ? -(static_cast<long long>(n)) : static_cast<long long>(n);

    long long reversed{0};
    while (value > 0) {
      reversed = reversed * 10 + value % 10; // append last digit
      value /= 10;
    }
    return negative ? -reversed : reversed;
  }
};

int main() {
  Solution sol;
  std::cout << sol.reverseDigits(1221) << '\n';   // 1221
  std::cout << sol.reverseDigits(12345) << '\n';  // 54321
  std::cout << sol.reverseDigits(-456) << '\n';   // -654 (original gave 0)
  return 0;
}
