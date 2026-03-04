#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void Transpose(vector<vector<int>> &matrix) {
  for (int i = 0, e = matrix.size(); i != e; ++i) {
    for (int j = 0; j < i; ++j) {
      int temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }
}

class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    Transpose(matrix);
    for (vector<int> &e : matrix) {
      reverse(e.begin(), e.end());
    }
  }
};

int main() {
  Solution sol;
  vector<vector<int>> mat = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  sol.rotate(mat);
  return 0;
}
