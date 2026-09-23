#include <bits/stdc++.h>
using namespace std;

// check the previous state
// check if valid path
// if not then backtrack

void backtrace(int t_i, int w_i, int w_j, vector<vector<char>> &words,
               string target, bool possible) {}

bool dfs(vector<vector<char>> &words, string target) {}

bool search(vector<vector<char>> &words, string target) {
  for (int i{}; i < words.size(); ++i) {
    for (int j{}; j < words[0].size(); ++j) {
      if (words[i][j] == target[0]) {
        if (dfs(words, target)) {
          return true;
        }
      }
    }
  }
  return false;
}
