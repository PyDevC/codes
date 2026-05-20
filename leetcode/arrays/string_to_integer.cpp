#include <iostream>
#include <limits>
#include <string>
using namespace std;

class Solution {
public:
  int myAtoi(string s) {
    int number = 0;

    int max_limit = std::numeric_limits<int>::max();
    int min_limit = std::numeric_limits<int>::min();

    bool is_negative = false;
    bool leading_symbols = true;

    for (char c : s) {
      if (leading_symbols) {
        if (c == ' ') {
          continue;
        } else if (c == '+') {
          leading_symbols = false;
          continue;
        } else if (c == '-') {
          leading_symbols = false;
          is_negative = true;
          continue;
        } else if (c >= '0' && c <= '9') {
          leading_symbols = false;
        } else {
          break;
        }
      }

      if (!(c >= '0' && c <= '9')) {
        break;
      }

      int digit = c - '0';
      if (number > max_limit / 10 || (number == max_limit / 10 && digit > 7)) {
        return is_negative? min_limit : max_limit;
      }

      number = (number * 10) + digit;
    }

    if (is_negative) {
      number = -number;
    }

    return number;
  }
};

int main(void) {
  Solution sol;
  cout << sol.myAtoi("-91283472332") << endl;
}
