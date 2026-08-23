#include <iostream>
#include <string>

class Solution {
public:
  std::string reverses(std::string &s) {
    int left{}, right{static_cast<int>(s.length()) - 1};
    while (left < right) {
      if (s[left] == ' ') {
        left++;
        continue;
      }
      if (s[right] == ' ') {
        right--;
        continue;
      }
      char temp = s[left];
      s[left] = s[right];
      s[right] = temp;
      left++;
      right--;
    }
    return s;
  }
};

int main() {
  Solution sol;
  std::string s = "Help others";
  std::cout << sol.reverses(s) << std::endl;
  return 0;
}
