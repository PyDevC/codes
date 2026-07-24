#include <iostream>
#include <stack>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

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
  int maxDepth(TreeNode *root) {
    if (!root) {
      return 0;
    }
    std::stack<std::pair<TreeNode *, int>> nodeStack{};
    nodeStack.push({root, 1});
    int depth{1};
    while (!nodeStack.empty()) {
      auto [currNode, d] = nodeStack.top();
      nodeStack.pop();
      depth = std::max(depth, d);
      if (currNode->left) {
        nodeStack.push({currNode->left, d + 1});
      }
      if (currNode->right) {
        nodeStack.push({currNode->right, d + 1});
      }
    }
    return depth;
  }
};

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  Solution sol;
  std::cout << sol.maxDepth(root);
  return 0;
}
