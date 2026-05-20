#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows == 1)
      return s;

    int i = 0;
    int direction = -1;
    int n = s.length();
    if (n <= numRows)
      return s;

    vector<string> coordinates(numRows);

    for (char c : s) {
      coordinates[i] += c;
      if (i == numRows - 1 || i == 0) {
        direction = -direction;
      }
      i += direction;
    }

    string zigzag;

    for (string v : coordinates) {
      zigzag += v;
    }

    return zigzag;
  }
};

int main(void) {
  Solution sol;
  string question = "paypalishiring";
  int numRows = 3;
  cout << sol.convert(question, numRows) << endl;
  return 0;
}
