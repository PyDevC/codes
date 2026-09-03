#include <bits/stdc++.h>
using namespace std;

// just for reference
string generate(int i, int n) {
  string str(n, '.');
  str[i] = 'Q';
  return str;
}

// prevState {row, col}
bool checkValid(int row, int col, vector<int> &prevState) {
  for (int i{}; i < row; ++i) {
    auto prow = i;
    auto pcol = prevState[i];
    if (pcol == col || std::abs(row - prow) == std::abs(col - pcol)) {
      return false;
    }
  }
  return true;
}

void backtrace(int row, int n, vector<int> &prevState,
               vector<vector<string>> &result, vector<string> &path) {
  if (row == n) {
    result.push_back(path);
    return;
  }

  for (int col{}; col < n; ++col) {
    if (checkValid(row, col, prevState)) {
      prevState[row] = col;
      path.push_back(generate(col, n));
      backtrace(row + 1, n, prevState, result, path);
      prevState[row] = -1;
      path.pop_back();
    }
  }
}

vector<vector<string>> solveNQueens(int n) {
  vector<int> prevState(n, -1);
  vector<string> path{};
  vector<vector<string>> result{};

  backtrace(0, n, prevState, result, path);
  return result;
}

int main() {
  int n = 4;
  auto out = solveNQueens(n);
  cout << "[";
  for (auto arr : out) {
    cout << "[";
    for (auto s : arr) {
      cout << s << ", ";
    }
    cout << "], ";
  }
  cout << "]";
  return 0;
}
