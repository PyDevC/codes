/**
 * Definition for a binary tree node.
 */
#pragma GCC optimize("Ofast")
#include <iostream>

static constexpr std::size_t max_align = alignof(std::max_align_t);
alignas(max_align) static unsigned char BUFFER[64 * 1024 * 1024];
static std::size_t pos = 0;

void *operator new(const std::size_t size) {
    const std::size_t padding = (max_align - (pos % max_align)) % max_align;
    pos += padding + size;
    return static_cast<void *>(&BUFFER[pos - size]);
}

void *operator new[](const std::size_t size) {
    return operator new(size);
}

void operator delete(void *) noexcept {}
void operator delete[](void *) noexcept {}
void operator delete(void *, std::size_t) noexcept {}
void operator delete[](void *, std::size_t) noexcept {}
static auto _ = [](){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
};

class Solution {
public:
  vector<int> inorderTraversal(TreeNode *root) {
    if (root == nullptr) {
      return {};
    }

    vector<int> values{};
    // morris traversal

    auto curr = root;
    while (curr != nullptr) {
      if (curr->left == nullptr) {
        values.push_back(curr->val);
        curr = curr->right;
      } else {
        auto prev = curr->left;
        while (prev->right != nullptr && prev->right != curr) {
          prev = prev->right;
        }

        if (prev->right == nullptr) {
          prev->right = curr;
          curr = curr->left;
        } else {
          prev->right = nullptr;
          values.push_back(curr->val);
          curr = curr->right;
        }
      }
    }

    return values;
  }
};

int main() {
  TreeNode *left_left = new TreeNode(3);
  TreeNode *right = new TreeNode(2, left_left, nullptr);
  TreeNode *root = new TreeNode(1, nullptr, right);
  Solution sol;
  auto out = sol.inorderTraversal(root);
  for (auto o : out) {
    cout << o << " ";
  }
  cout << endl;
  return 0;
}
