#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcmt,popcnt")

class Solution {
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[10]; // set -1 for false and 0 for true;
        int column[10];
        int box[10];

        for (int i = 0; i < 9; ++i) {
            std::fill(row, row + 10, -1);
            std::fill(column, column+ 10, -1);
            std::fill(box, box + 10, -1);
            for (int j = 0; j < 9; ++j) {
                int r = board[i][j] == '.'? 0: board[i][j] - '0';
                int c = board[j][i] == '.'? 0: board[j][i] - '0';
                int b_r = (i / 3) * 3 + (j / 3);
                int b_c = (i % 3) * 3 + (j % 3);
                int b = board[b_r][b_c] == '.'? 0: board[b_r][b_c] - '0';

                if ((row[r] == 0 && r != 0) || (column[c] == 0 && c != 0) || (box[b] == 0 && b != 0)) { return false; }
                row[r] = 0;
                column[c] = 0;
                box[b] = 0;
            }
        }

        return true;
    }

    bool back_trace(int i, int j, vector<vector<char>>& board) {
        if (i == 8 && j == 9) return true;

        if(j == 9) {
            i++;
            j = 0;
        }

        if (board[i][j] != '.') {
            return back_trace(i, j + 1, board);
        }

        for(int k = 1; k <= 9; ++k) {
            board[i][j] = k + '0';
            if(isValidSudoku(board)) {
                if(back_trace(i, j + 1, board)) {
                    return true;
                }
            }
            board[i][j] = '.';
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        back_trace(0, 0, board);
    }
};


int main() {
    Solution sol;
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    sol.solveSudoku(board);

    for(auto &b: board) {
        std::cout << "[";
        for(auto &v : b) {
            std::cout << v << " ";
        }
        std::cout << "]\n";
    }
    return 0;
}
