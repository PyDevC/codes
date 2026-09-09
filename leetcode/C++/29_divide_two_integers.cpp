#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int divide(int dividend, int divisor) {
    if (dividend == INT_MAX && divisor == -1)
      return INT_MAX;

    bool sign = (divisor < 0 || dividend < 0);
    divisor = std::abs(divisor);
    dividend = std::abs(dividend);
    long long answer{};

    for (int i{31}; i >= 0; --i) {
      if ((divisor << i) <= dividend) {
        dividend -= (divisor << i);
        answer |= (1LL << i);
      }
    }

    return sign ? -answer : answer;
  }
};
