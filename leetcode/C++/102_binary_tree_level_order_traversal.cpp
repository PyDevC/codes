#include <iostream>
#include <queue>
#include <vector>

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
  std::vector<std::vector<int>> levelOrder(TreeNode *root) {
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> results{};
    std::queue<TreeNode *> nodeQueue{};
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
      auto levelLength{nodeQueue.size()};
      results.push_back({});
      for (int i{}; i < levelLength; ++i) {
        auto currNode = nodeQueue.front();
        nodeQueue.pop();
        if (currNode->left) {
          nodeQueue.push(currNode->left);
        }
        if (currNode->right) {
          nodeQueue.push(currNode->right);
        }
        results.back().push_back(currNode->val);
      }
    }
    return results;
  }
};

int main() {
  TreeNode *root = new TreeNode(4);
  root->left = new TreeNode(2);
  root->right = new TreeNode(6);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(5);

  Solution sol;
  auto result = sol.levelOrder(root);
  std::cout << "[";
  for (auto res : result) {
    std::cout << "[";
    for (auto r : res) {
      std::cout << r << ", ";
    }
    std::cout << "\b\b] ";
  }
  std::cout << "\b]";
  return 0;
}
