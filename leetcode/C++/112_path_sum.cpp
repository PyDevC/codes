/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
  bool helper(TreeNode *root, int targetSum) {
    if (!root->left && !root->right) {
      return targetSum == root->val;
    }

    bool check = false;
    check = std::max(check, helper(root->left, targetSum - root->val));
    check = std::max(check, helper(root->right, targetSum - root->val));
    return check;
  }

public:
  bool hasPathSum(TreeNode *root, int targetSum) {
    if (!root)
      return false;
    return helper(root, targetSum);
  }
};
