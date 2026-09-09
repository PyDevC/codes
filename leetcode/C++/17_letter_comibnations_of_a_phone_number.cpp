#include <bits/stdc++.h>
using namespace std;

class Solution {
  unordered_map<char, string> char_map{
      {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
      {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
  };

  void combinatorics(int i, string &digits, vector<string> &result,
                     string &path) {
    if (i == digits.size()) {
      result.push_back(path);
      return;
    }

    for (int j{}; j < char_map[digits[i]].size(); ++j) {
      path.push_back(char_map[digits[i]][j]);
      combinatorics(i + 1, digits, result, path);
      path.pop_back();
    }
  }

public:
  vector<string> letterCombinations(string digits) {
    vector<string> result{};
    string path{};
    combinatorics(0, digits, result, path);
    return result;
  }
};

int main() {
  Solution sol;
  auto answer = sol.letterCombinations("23");
  std::cout << "[ ";
  for (auto ans : answer) {
    cout << "\"" << ans << "\", ";
  }
  std::cout << "\b\b ]" << std::endl;
  return 0;
}
