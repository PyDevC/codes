#include <string>
#include "helper.hpp"

class Solution {
  public:
    std::vector<std::string> extractInt(std::string &s) {
        std::vector<std::string> result{};
        
        int startDigit{-1};
        for(int i{}; i < s.length(); ++i) {
            if(isdigit(s[i])) {
                startDigit = i;
            }
            while(isdigit(s[i])) {
                ++i;
            }

            if(startDigit >= 0) {
                auto number = s.substr(startDigit, i - startDigit);
                result.push_back(number);
                startDigit = -1;
            }
        }
        return result;
    }
};

int main() {
    std::string s = "1: Geeks for geeks, 2: geeksfor geeks, 3: forGeeksgeeks 56";
    Solution sol;
    auto numbers = sol.extractInt(s);
    printVector(numbers);
}
