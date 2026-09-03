#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  bool stoneGameIX(vector<int> &stones) {
    int cnt[3] = {};
    for (auto stone : stones) {
      ++cnt[stone % 3];
    }

    return cnt[0] % 2 == 0 ? cnt[1] >= 1 && cnt[2] >= 1
                           : abs(cnt[1] - cnt[2]) > 2;
  }
};
