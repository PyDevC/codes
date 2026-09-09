#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int strStr(string haystack, string needle) {
    int limit = haystack.size();
    int searchIdx{};
    int width = needle.size();
    string_view haystack_view{haystack};

    while (searchIdx < limit) {
      if (haystack_view[searchIdx] == needle[0]) {
        if (haystack_view.substr(searchIdx, width) == needle) {
          return searchIdx;
        }
      }
      ++searchIdx;
    }

    return -1;
  }
};

int main() {
  Solution sol;
  cout << sol.strStr("sadbuts", "but") << endl;
  return 0;
}
