#include <bits/stdc++.h>
using namespace std;

class Solution {
  void backtrace(int i, int j, int n, vector<string> &result, string &path) {
    if (i == n && j == n) {
      result.push_back(path);
      return;
    } else if (i > n || j > n) {
      return;
    }

    path += "(";
    backtrace(i + 1, j, n, result, path);
    path.pop_back();
    if (j < i) {
      path += ")";
      backtrace(i, j + 1, n, result, path);
      path.pop_back();
    }
  }

public:
  vector<string> generateParenthesis(int n) {
    vector<string> result{};
    string path = "(";
    backtrace(1, 0, n, result, path);

    return result;
  }
};
