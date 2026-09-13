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
#include <bits/stdc++.h>
using namespace std;

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
  TreeNode *getRoot(int preIndex, vector<int> &preorder) {
    return new TreeNode(preorder[preIndex]);
  }

  int searchForRoot(int left, int right, int value, vector<int> &inorder) {
    for (int i{left}; i < right; ++i) {
      if (value == inorder[i]) {
        return i;
      }
    }
    return -1; // This will not occur but whatever
  }

  TreeNode *generateTree(int preIndex, int left, int right,
                         vector<int> &preorder, vector<int> &inorder) {
    if (left > right) {
      // Null Node
      return nullptr;
    }

    auto root = getRoot(preIndex, preorder);
    int idx = searchForRoot(left, right, root->val, inorder);
    root->left = generateTree(preIndex + 1, left, idx - 1, preorder, inorder);
    root->right = generateTree(preIndex + 1, idx + 1, right, preorder, inorder);
    return root;
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    auto root = generateTree(0, 0, preorder.size() - 1, preorder, inorder);
    return root;
  }
};
