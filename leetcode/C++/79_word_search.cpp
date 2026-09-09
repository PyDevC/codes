#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool recusive_path(int idx, int i, int j, vector<vector<char>> &board,
                     string &word) {
    if (idx == word.size()) {
      return true;
    }

    if (i < 0 || j < 0 || i == board.size() || j == board[0].size() ||
        board[i][j] != word[idx]) {
      return false;
    }

    char visited = board[i][j];
    board[i][j] = '.';

    bool found = false;

    found = std::max(found, recusive_path(idx + 1, i + 1, j, board, word));
    found = std::max(found, recusive_path(idx + 1, i - 1, j, board, word));
    found = std::max(found, recusive_path(idx + 1, i, j + 1, board, word));
    found = std::max(found, recusive_path(idx + 1, i, j - 1, board, word));
    board[i][j] = visited;

    return found;
  }

public:
  bool exist(vector<vector<char>> &board, string word) {
    // Optimizations
    if (std::count(word.begin(), word.end(), word.front()) >
        std::count(word.begin(), word.end(), word.back())) {
      std::reverse(word.begin(), word.end());
    }

    for (int i{}; i < board.size(); ++i) {
      for (int j{}; j < board[0].size(); ++j) {
        if (word[0] == board[i][j] && recusive_path(0, i, j, board, word)) {
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  vector<vector<char>> board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

  Solution sol;
  cout << sol.exist(board, "ABFD") << endl;
  return 0;
}
