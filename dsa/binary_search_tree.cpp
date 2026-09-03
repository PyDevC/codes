class Node {
private:
  Node *m_Left;
  Node *m_Right;
  int m_Value;

  void createNodeInTree(Node *parent, int value) {
    if (parent->m_Value > value) {
      if (parent->m_Left == nullptr) {
        parent->m_Left = new Node(value);
      } else {
        parent->m_Left->createNodeInTree(parent->m_Left, value);
      }
    } else {
      if (parent->m_Right == nullptr) {
        parent->m_Right = new Node(value);
      } else {
        parent->m_Right->createNodeInTree(parent->m_Right, value);
      }
    }
  }

  Node *search(int value) {
    if (m_Value == value) {
      return this;
    }

    if (m_Value > value) {
      if (m_Left == nullptr) {
        return nullptr;
      }
      return m_Left->search(value);
    } else {
      if (m_Right == nullptr) {
        return nullptr;
      }
      return m_Right->search(value);
    }
  }

public:
  Node(int value) : m_Value(value), m_Left(nullptr), m_Right(nullptr) {}
  Node(int value, Node *left, Node *right)
      : m_Value(value), m_Left(left), m_Right(right) {}

  void addNode(int value) { createNodeInTree(this, value); }
  Node *searchNodeByValue(int value) { return search(value); }
};

int main() {
  Node *root = new Node(10);
  root->addNode(20);
  root->addNode(3);
  root->addNode(40);
  root->addNode(4);
  return 0;
}
