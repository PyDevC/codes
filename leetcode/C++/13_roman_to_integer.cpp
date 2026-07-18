#include <iostream>
#include <unordered_map>

class Solution {
  std::unordered_map<char, int> map = {
      {'I', 1},   {'V', 5},   {'X', 10},   {'L', 50},
      {'C', 100}, {'D', 500}, {'M', 1000},
  };

public:
  int romanToInt(std::string s) {
    if (s.empty()) {
      return 0;
    } else if (s.size() == 1) {
      return map[s[0]];
    }

    int result{};
    int prevValue{};

    for (auto i{s.size()}; i > 0; --i) {
      auto currValue = map[s[i - 1]];
      if (prevValue > currValue) {
        result -= currValue;
      } else {
        result += currValue;
      }
      prevValue = currValue;
    }

    return result;
  }
};

int main() {
  Solution sol;
  std::cout << sol.romanToInt("MCMXCIV");
  return 0;
}
