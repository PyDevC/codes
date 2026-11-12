#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        // { {row 1 }, {row 2}, ... }
        std::vector<std::string> result(numRows, "");

        int i = 0, k = 1;

        for(char &c : s) {
            result[i] += c;
            if (i >= numRows - 1) {
                k = -1;
            } else if (i <= 0) {
                k = 1;
            }

            i += k;
        }

        // merge all numRows vetor into a string
        std::string answer = "";
        for (auto &row : result) {
            answer += row;
        }

        return answer;
    }
};
