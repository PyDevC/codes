#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    if (!root)
      return {};

    vector<vector<int>> result{};
    queue<TreeNode *> nodeQueue{};
    nodeQueue.push(root);
    bool doreverse = false;
    while (!nodeQueue.empty()) {
      int currLen = nodeQueue.size();
      result.push_back({});
      for (int i{}; i < currLen; ++i) {
        auto curr = nodeQueue.front();
        nodeQueue.pop();
        result.back().push_back(curr->val);
        if (curr->left)
          nodeQueue.push(curr->left);
        if (curr->right)
          nodeQueue.push(curr->right);
      }
      if (doreverse) {
        reverse(result.back().begin(), result.back().end());
      }
      doreverse = !doreverse; // flip
    }
    return result;
  }
};
