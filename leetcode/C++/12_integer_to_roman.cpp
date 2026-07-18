#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
private:
  const std::vector<std::pair<int, const std::string>> map = {
      {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
      {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
      {5, "V"},    {4, "IV"},   {1, "I"},
  };

public:
  std::string intToRoman(int num) {
    std::string result{};

    for (const auto &[value, symbol] : map) {
      while (num >= value) {
        result += symbol;
        num -= value;
      }
    }

    return result;
  }
};

int main() {
  Solution sol;
  std::cout << sol.intToRoman(10) << "\n";
  std::cout << sol.intToRoman(11) << "\n";
  std::cout << sol.intToRoman(3749) << "\n";
  std::cout << sol.intToRoman(13) << "\n";
  return 0;
}
