#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxNumberOfFamilies(int n, vector<vector<int>> &reservedSeats) {
    sort(reservedSeats.begin(), reservedSeats.end());
    int result{};

    int j{};
    int m = static_cast<int>(reservedSeats.size());
    for (int i{}; i < n; ++i) {
      bool middleSeats{true};
      bool firstSeats{true};
      bool lastSeats{true};

      while (j < m && reservedSeats[j][0] == i + 1) {
        if (reservedSeats[j][1] == 2 || reservedSeats[j][1] == 3) {
          firstSeats = false;
          j++;
          continue;
        }
        if (reservedSeats[j][1] == 4 || reservedSeats[j][1] == 5) {
          firstSeats = false;
          middleSeats = false;
          j++;
          continue;
        }
        if (reservedSeats[j][1] == 6 || reservedSeats[j][1] == 7) {
          middleSeats = false;
          lastSeats = false;
          j++;
          continue;
        }
        if (reservedSeats[j][1] == 8 || reservedSeats[j][1] == 9) {
          lastSeats = false;
          j++;
          continue;
        }
        j++;
      }

      if (firstSeats && lastSeats) {
        result += 2;
      } else {
        result += (firstSeats || middleSeats || lastSeats);
      }
    }
    return result;
  }
};

int main() {
  vector<vector<int>> reservedSeats = {{2, 1}, {1, 8}, {2, 6}};
  int n = 2;
  Solution sol;
  cout << sol.maxNumberOfFamilies(n, reservedSeats) << endl;
}
