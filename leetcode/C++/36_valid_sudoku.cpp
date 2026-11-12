#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int checker[9]; // set -1 for false and 0 for true;

        // row checking
        for (int i = 0; i < 9; ++i) {
            std::fill(checker, checker + 9, -1);
            for (int j = 0; j < 9; ++j) {
                char val = board[i][j];
                if(val == '.') continue;
                int num = val - '1';

                if (checker[num] == 0) {
                    return false;
                }
                checker[num] = 0;
            }
        }

        for (int i = 0; i < 9; ++i) {
            std::fill(checker, checker + 9, -1);
            for (int j = 0; j < 9; ++j) {
                char val = board[j][i];
                if(val == '.') continue;
                int num = val - '1';

                if (checker[num] == 0) {
                    return false;
                }
                checker[num] = 0;
            }
        }

        for (int i = 0; i < 9; ++i) {
            std::fill(checker, checker + 9, -1);
            for (int j = 0; j < 9; ++j) {
                int r = (i / 3) * 3 + (j / 3);
                int c = (i % 3) * 3 + (j % 3);

                char val = board[r][c];
                if(val == '.') continue;
                int num = val - '1';

                if (checker[num] == 0) {
                    return false;
                }
                checker[num] = 0;
            }
        }

        return true;
    }
};
