#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    for (int i = (digits.size() - 1); i >= 0; --i) {
      if (digits[i] < 9) {
        digits[i]++;
        return digits;
      } else {
        digits[i] = 0;
      }
    }

    digits.insert(digits.begin(), 1);

    return digits;
  }
};

int main() {
  vector<int> digits = {9, 9, 9};
  Solution sol;
  auto out = sol.plusOne(digits);
  for (auto o : out) {
    cout << o << ", ";
  }
  cout << endl;
  return 0;
}
