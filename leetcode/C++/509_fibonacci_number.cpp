#include <cassert>
#include <iostream>

class Solution {
public:
  int fib(int n) {
    if (n == 0) return 0;
    if (n < 3) return 1;

    int prevResult{1};
    int result{1};

    for (int i{2}; i < n; ++i) {
      int tempResult = result;
      result = result + prevResult;
      prevResult = tempResult;
    }

    return result;
  }
};

int main() {
  int ans[] = {0,     1,     1,      2,      3,      5,      8,     13,
               21,    34,    55,     89,     144,    233,    377,   610,
               987,   1597,  2584,   4181,   6765,   10946,  17711, 28657,
               46368, 75025, 121393, 196418, 317811, 514229, 832040};

  Solution sol;
  int i = 0;
  for (int a : ans) {
    assert(sol.fib(i) == a);
    ++i;
  }
  return 0;
};
