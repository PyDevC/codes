#include <bits/stdc++.h>
using namespace std;

class Solution {
  string generate(int col, int n) {
    string str(n, '.');
    str[col] = 'Q';
    return str;
  }

  bool checkValid(int row, int col, vector<int> &prevColState) {
    for (int i{}; i < row; ++i) {
      int prow = i;
      int pcol = prevColState[i];
      if (pcol == col || std::abs(pcol - col) == std::abs(prow - row)) {
        return false;
      }
    }
    return true;
  }

  void backtrace(int row, int n, vector<vector<string>> &result,
                 vector<int> &prevRowState, vector<string> &path) {
    if (row == n) {
      result.push_back(path);
      return;
    }

    for (int col{}; col < n; ++col) {
      if (checkValid(row, col, prevRowState)) {
        prevRowState[row] = col;
        path.push_back(generate(col, n));
        backtrace(row + 1, n, result, prevRowState, path);
        path.pop_back();
        prevRowState[row] = -1;
      }
    }
  }

public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result{};
    vector<int> prevRowState(n, -1);
    vector<string> path{};
    backtrace(0, n, result, prevRowState, path);
    return result;
  }
};
