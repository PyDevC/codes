#include <iostream>
#include <limits>
using namespace std;

class Solution {
public:
  int reverse(int x) {
    int reversed = 0;
    int int_max = std::numeric_limits<int>::max();
    int int_min = std::numeric_limits<int>::min();

    while (x != 0) {
      int remainder = x % 10;
      x = x / 10;

      if (reversed > int_max / 10 ||
          (reversed == int_max / 10 && remainder > 7)) {
        return 0;
      }
      if (reversed < int_min / 10 ||
          (reversed == int_min / 10 && remainder < -8)) {
        return 0;
      }

      reversed = (reversed * 10) + remainder;
    }

    return reversed;
  }
};

int main(void) {
  Solution sol;
    cout << sol.reverse(-2143847412) << endl;
  return 0;
}
