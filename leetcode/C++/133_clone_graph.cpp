#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Node {
public:
  int val;
  std::vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = std::vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = std::vector<Node *>();
  }
  Node(int _val, std::vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

Node *create_graph(std::vector<std::vector<int>> &nodes) {
  int n = nodes.size();
  std::vector<Node *> generatedNodes{};
  for (int i{}; i < n; ++i) {
    generatedNodes.push_back(new Node(i + 1));
  }

  for (int i{}; i < n; ++i) {
    std::cout << generatedNodes[i]->val << std::endl;
    for (int j{}; j < nodes[i].size(); ++j) {
      generatedNodes[i]->neighbors.push_back(generatedNodes[nodes[i][j] - 1]);
    }
  }

  return generatedNodes[0];
}

void printGraph(Node *root) {
  if (!root)
    return;

  std::unordered_set<int> visited;
  std::stack<Node *> nodeStack;
  nodeStack.push(root);

  while (!nodeStack.empty()) {
    auto curr = nodeStack.top();
    nodeStack.pop();

    if (visited.count(curr->val)) {
      continue;
    }
    visited.insert(curr->val);
    std::cout << curr->val << std::endl;

    for (auto neighbor : curr->neighbors) {
      if (!visited.count(neighbor->val)) {
        nodeStack.push(neighbor);
      }
    }
  }
}

class Solution {
  std::unordered_map<Node *, Node *> clone;
  void dfs(Node *node) {
    if (!node) {
      return;
    }

    Node *newNode = new Node(node->val);
    clone[node] = newNode;
    for (auto &n : node->neighbors) {
      if (clone.find(n) == clone.end()) {
        dfs(n);
      }
      newNode->neighbors.push_back(clone[n]);
    }
  }

public:
  Node *cloneGraph(Node *node) {
    if (!node) {
      return nullptr;
    }
    dfs(node);
    return clone[node];
  }
};

int main() {
  std::vector<std::vector<int>> nodes = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};
  Node *root = create_graph(nodes);
  Solution sol;
  auto newRoot = sol.cloneGraph(root);
  std::cout << "Old Graph" << std::endl;
  printGraph(root);
  std::cout << "New Graph" << std::endl;
  printGraph(newRoot);
  return 0;
}
