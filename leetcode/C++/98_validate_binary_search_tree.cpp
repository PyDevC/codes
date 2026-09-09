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
  bool isBST(TreeNode *node, long long int minval, long long int maxval) {
    if (node == nullptr)
      return true;

    if (node->val < minval || node->val > maxval) {
      return false;
    }

    bool check = false;
    check = std::min(check, isBST(node->left, minval, node->left->val));
    check = std::min(check, isBST(node->right, node->right->val, maxval));

    return check;
  }

public:
  bool isValidBST(TreeNode *root) {
    if (!root)
      return false;

    return isBST(root, LLONG_MIN, LLONG_MAX);
  }
};

int main() { return 0; }
