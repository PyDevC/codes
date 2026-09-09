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
public:
  void flatten(TreeNode *root) {
    if (!root)
      return;

    flatten(root->left);
    flatten(root->right);
    if (root->left) {
      auto temp = root->right;
      root->right = root->left;
      if (temp) {
        auto curr = root->right;
        while (curr->right != nullptr) {
          curr = curr->right;
        }
        curr->right = temp;
      }
    }
  }
};
