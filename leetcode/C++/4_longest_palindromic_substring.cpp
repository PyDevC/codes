#include <algorithm>
#include <iostream>
#include <string>

class Solution {
  bool checkPalindrome(std::string s) {
    std::string rev = s;
    std::reverse(rev.begin(), rev.end());
    return s == rev;
  }

public:
  std::string longestPalindrome(std::string s) {
    if (s.empty()) {
      return "";
    }

    int length = static_cast<int>(s.length());
    int palindromeMaxLen{};
    std::string palindromeString{};

    for (int left{}; left < length; ++left) {
      for (int right{left}; right <= length; ++right) {
        auto sub = s.substr(left, right - left + 1);
        if (checkPalindrome(sub)) {
          if (palindromeMaxLen < sub.size()) {
            palindromeMaxLen = sub.size();
            palindromeString = sub;
          }
        }
      }
    }
    return palindromeString;
  }
};

int main() {
  Solution sol;
  std::cout
      << sol.longestPalindrome(
             "klvxwqyzugrdoaccdafdfrvxiowkcuedfhoixzipxrkzbvpusslsgfjocvidnpsnk"
             "qdfnnzzawzsslwnvvjyoignsfbxkgrokzyusxikxumrxlzzrnbtrixxfioormoyye"
             "jashrowjqqzifacecvoruwkuessttlexvdptuvodoavsjaepvrfvbdhumtuvxufzz"
             "yowiswokioyjtzzmevttheeyjqcldllxvjraeyflthntsmipaoyjixygbtbvbnnrm"
             "lwwkeikhnnmlfspjgmcxwbjyhomfjdcnogqjviggklplpznfwjydkxzjkoskvqvnx"
             "fzdrsmooyciwulvtlmvnjbbmffureoilszlonibbcwfsjzguxqrjwypwrskhrttvn"
             "qoqisdfuifqnabzbvyzgbxfvmcomneykfmycevnrcsyqclamfxskmsxreptpxqxqi"
             "dvjbuduktnwwoztvkuebfdigmjqfuolqzvjincchlmbrxpqgguwuyhrdtwqkdlqid"
             "lxzqktgzktihvlwsbysjeykiwokyqaskjjngovbagspyspeghutyoeahhgynzsyas"
             "zlirmlekpboywqdliumihwnsnwjc")
      << std::endl;
  return 0;
}
