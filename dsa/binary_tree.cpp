#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

enum Order { Pre, In, Post };

template <typename T> class BinaryTree {
private:
  struct m_Node {
    T data;
    std::unique_ptr<m_Node> left;
    std::unique_ptr<m_Node> right;

    m_Node(T data) : data(std::move(data)) {}
  };

  std::unique_ptr<m_Node> m_root;

public:
  BinaryTree() = default;
  void insert(T data) {
    if (!m_root) {
      m_root = std::make_unique<m_Node>(std::move(data));
      return;
    }

    std::queue<m_Node *> q;
    q.push(m_root.get());
    while (!q.empty()) {
      auto curr = q.front();
      q.pop();
      if (!curr->left) {
        curr->left = std::make_unique<m_Node>(std::move(data));
        return;
      } else {
        q.push(curr->left.get());
      }
      if (!curr->right) {
        curr->right = std::make_unique<m_Node>(std::move(data));
        return;
      } else {
        q.push(curr->right.get());
      }
    }
  }

  std::vector<T> dfs(Order order) const {
    std::vector<T> result{};
    if (m_root == nullptr) {
      return result;
    }

    std::stack<const m_Node *> nodeStack;

    switch (order) {
    case Pre: {
      nodeStack.push(m_root.get());
      while (!nodeStack.empty()) {
        const m_Node *curr = nodeStack.top();
        nodeStack.pop();
        result.push_back(curr->data);
        if (curr->right) {
          nodeStack.push(curr->right.get());
        }
        if (curr->left) {
          nodeStack.push(curr->left.get());
        }
      }
    } break;

    case In: {
      const m_Node *curr = m_root.get();
      while (curr != nullptr || !nodeStack.empty()) {
        while (curr != nullptr) {
          nodeStack.push(curr);
          curr = curr->left.get();
        }
        curr = nodeStack.top();
        nodeStack.pop();
        result.push_back(curr->data);
        curr = curr->right.get();
      }
    } break;

    case Post: {
      nodeStack.push(m_root.get());
      while (!nodeStack.empty()) {
        const m_Node *curr = nodeStack.top();
        nodeStack.pop();
        result.push_back(curr->data);
        if (curr->left)
          nodeStack.push(curr->left.get());
        if (curr->right)
          nodeStack.push(curr->right.get());
      }
      std::reverse(result.begin(), result.end());
    } break;
    };

    return result;
  }
  std::vector<std::vector<T>> bfs() const {
    std::vector<std::vector<T>> result;
    if (m_root == nullptr) {
      return result;
    }

    std::queue<m_Node *> nodeQueue;
    nodeQueue.push(m_root.get());
    while (!nodeQueue.empty()) {
      auto currLen{nodeQueue.size()};
      result.push_back({});
      for (int i{}; i < currLen; ++i) {
        const m_Node *curr = nodeQueue.front();
        nodeQueue.pop();

        result.back().push_back(curr->data);

        if (curr->left) {
          nodeQueue.push(curr->left.get());
        }
        if (curr->right) {
          nodeQueue.push(curr->right.get());
        }
      }
    }
    return result;
  }
};

int main() {
  BinaryTree<int> bTree{};
  for (int i{}; i < 10; ++i) {
    bTree.insert(i);
  }
  auto results = bTree.dfs(Post);
  for (auto node : results) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
  return 0;
}
