#include <bits/stdc++.h>
using namespace std;

int countFunc;

int recursive_lcs(int i, int j, int k, string &s1, string &s2, string &s3,
                  vector<vector<vector<int>>> &dp) {
  if (i >= s1.size() || j >= s2.size() || k >= s3.size()) {
    return 0;
  }

  if (dp[i][j][k] != -1) {
    return dp[i][j][k];
  }

  int ans = 0;
  // All three case
  ans = max(ans, recursive_lcs(i + 1, j, k, s1, s2, s3, dp));
  ans = max(ans, recursive_lcs(i, j + 1, k, s1, s2, s3, dp));
  ans = max(ans, recursive_lcs(i, j, k + 1, s1, s2, s3, dp));

  if (s1[i] == s2[j] && s2[j] == s3[k]) {
    ans = max(ans, 1 + recursive_lcs(i + 1, j + 1, k + 1, s1, s2, s3, dp));
  }

  countFunc++;
  return dp[i][j][k] = ans;
}

int findLCSLength(string &s1, string &s2, string &s3) {
  vector<vector<vector<int>>> dp(
      s1.size(), vector<vector<int>>(s2.size(), vector<int>(s3.size(), -1)));

  return recursive_lcs(0, 0, 0, s1, s2, s3, dp);
}

int main() {
  string s1 =
      "slkdjfklsjfklsjdlkfsdljfsdlkjsdlfjsldjflskdjlsdkjflsksdlksdlkjsdlk";
  string s2 = "sldkfjjcslkfjlksdjflksdjklfjjcsljfldjlskjfldkjlsdjfsldkjjc";
  string s3 = "skjfiweskljfdljsdjdsfjdjdfkdjlksjflsjdlkfjdlkjsdlf";
  cout << findLCSLength(s1, s2, s3) << endl;
  cout << "Function Count " << countFunc << endl;
  return 0;
}
