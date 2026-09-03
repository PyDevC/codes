#include <cmath>
#include <iostream>

class Solution {
public:
  int closestNumber(int n, int m) {
    if (n == 0) {
      return m;
    }

    int first = (n / m) * m;
    int second{};
    if (n > 0) {
      second = ((n / m) + 1) * m;
    } else {
      second = ((n / m) - 1) * m;
    }

    return std::max(first, second, [&](auto a, auto b) {
      if ((n - first) == (n - second)) {
        return std::abs(first) > std::abs(second);
      } else {
        return (n - first) < (n - second);
      }
    });
  }
};

int main() {
  Solution sol;
  std::cout << sol.closestNumber(-15, 6) << std::endl;
  return 0;
}
