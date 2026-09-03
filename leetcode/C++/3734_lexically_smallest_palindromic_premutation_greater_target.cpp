#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
private:
    bool possiblePermutation(std::string &s) {
        if (s.empty()) { return false; }

        std::unordered_map<char, int> freq{};
        for (char c : s) {
            freq[c]++;
        }

        // TODO: Can be trimmed to smaller code
        if(s.length() % 2 == 0) {
            for(auto it{freq.begin()}; it != freq.end(); ++it) {
                if(it->second % 2 != 0) {
                    return false;
                }
            }
        } else {
            bool has_odd{};
            for(auto it{freq.begin()}; it != freq.end(); ++it) {
                if(it->second % 2 != 0) {
                    if (has_odd) {
                        return false;
                    } else {
                        has_odd = true;
                    }
                }
            }
        }

        return true;
    }

public:
    std::string lexPalindromicPermutation(std::string s, std::string target) {
        // std::string result{};
        if(possiblePermutation(s)) {
            return "True";
        } else {
            return "False";
        }
        // return result;
    }
};

int main() {
    std::string s = "baba";
    std::string t = "abba";
    Solution sol;
    std::cout << sol.lexPalindromicPermutation(s, t) << std::endl;
    return 0;
}
