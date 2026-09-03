// Problem Statement
// Given N X N chessboard you have to decide how many queens how many ways you
// can place N queens so no queens attach each other.

// Q - - - -
// - - Q - -
// - - - - Q
// - Q - - -
// - - - Q -
#include <iostream>
#include <vector>

bool checkValidState(int row, int col, std::vector<int> &prevStates) {
  for (int i{}; i < row; ++i) {
    auto prow = i;
    auto pcol = prevStates[i];
    if (pcol == col || std::abs(row - prow) == std::abs(col - pcol)) {
      return false;
    }
  }

  return true;
}

int recQueens(int level, int n, std::vector<int> &prevStates) {
  if (level == n) {
    return 1;
  }

  int ans{};
  for (int col{}; col < n; ++col) {
    if (checkValidState(level, col, prevStates)) {
      prevStates[level] = col;
      ans += recQueens(level + 1, n, prevStates);
      prevStates[level] = -1;
    }
  }
  return ans;
}

int nQueens(int n) {
  std::vector<int> prevStates(n, -1);
  return recQueens(0, n, prevStates);
}

int main() { std::cout << nQueens(8) << std::endl; }
