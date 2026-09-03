#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <typename T> class Node {
private:
  std::vector<Node *> m_Children;
  T m_Value;

  void dfs() {
    for (auto &child : m_Children) {
      if (child == nullptr) {
        continue;
      }
      child->dfs();
    }
    std::cout << this->m_Value << std::endl;
  }

  void bfs() {
    std::queue<Node *> nodeQueue{};
    nodeQueue.push(this);
    while (!nodeQueue.empty()) {
      auto tempNode = nodeQueue.front();
      std::cout << tempNode->m_Value << std::endl;
      nodeQueue.pop();
      for (auto &child : tempNode->m_Children) {
        nodeQueue.push(child);
      }
    }
  }

public:
  Node(T value) : m_Value(value) {}
  Node(T value, std::vector<Node *> children)
      : m_Value(value), m_Children(children) {}

  void addChild(Node *parent, Node *child) {
    parent->m_Children.push_back(child);
  }

  void removeChild(Node *parent, Node *child) {
    parent->m_Children.remove(child);
  }

  void printTree(const std::string &prefix = "") const {
    if (prefix.empty()) {
      std::cout << m_Value << std::endl;
    } else {
      std::cout << prefix << m_Value << std::endl;
    }

    for (auto &child : m_Children) {
      if (child == nullptr) {
        continue;
      }
      child->printTree(prefix + "|-> ");
    }
  }

  int findDegree() { return static_cast<int>(m_Children.size()); }

  int findHeight() {
    std::vector<int> heights{};
    if (m_Children.empty()) {
      return 0;
    }
    for (auto &child : m_Children) {
      if (child == nullptr) {
        continue;
      }
      heights.push_back(child->findHeight());
    }
    return 1 + (*std::max_element(heights.begin(), heights.end()));
  }

  void DFS() { this->dfs(); }
  void BFS() { this->bfs(); }
};

int main() {
  Node<int> *root = new Node<int>(10);
  Node<int> *child1 = new Node<int>(20);
  Node<int> *child2 = new Node<int>(30);
  Node<int> *grandchild = new Node<int>(40);

  root->addChild(root, child1);
  root->addChild(root, child2);
  root->addChild(child1, grandchild);
  // root->printTree();
  // root->DFS();
  std::cout << "Height of tree: " << root->findHeight() << std::endl;
  root->BFS();

  return 0;
}
