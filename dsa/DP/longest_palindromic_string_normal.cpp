#include <bits/stdc++.h>
using namespace std;

int countFunc;
bool isPalindrome(int start, int end, const string &s) {
  auto len = end - start + 1;
  for (int i{}; i < len / 2; ++i) {
    if (s[start + i] != s[end - i])
      return false;
  }
  return true;
}

void recursive_call(int j, string &s, string &result, vector<vector<int>> &dp) {
  if (j == s.size()) {
    return;
  }

  for (int i{}; i <= j; ++i) {
    if (dp[i][j] != -1) {
      continue;
    }

    bool ans = isPalindrome(i, j, s);
    dp[i][j] = ans;

    if (ans) {
      if (result.length() < (j - i + 1)) {
        result = s.substr(i, (j - i + 1));
      }
    }
    recursive_call(j + 1, s, result, dp);
  }
}

string lps(string &s) {
  string result = "";
  vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
  recursive_call(0, s, result, dp);
  return result;
}

int main() {
  string s =
      "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedca"
      "nlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpatea"
      "portionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatt"
      "hatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalar"
      "gersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebra"
      "velmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwe"
      "rtoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayhereb"
      "utitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedhe"
      "retotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedIt"
      "isratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromt"
      "hesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelast"
      "pfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavedi"
      "edinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernm"
      "entofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
  cout << lps(s) << endl;
  cout << "For " << s.size() << " size is " << countFunc << endl;
  return 0;
}
