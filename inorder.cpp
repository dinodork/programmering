#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  Node(char label) : m_label(label) {}
  Node(char label, Node *left, Node *right)
      : m_label(label), m_left(left), m_right(right) {
    if (m_left)
      m_left->m_parent = this;
    if (m_right)
      m_right->m_parent = this;
  }

  Node(char label, char left_label, Node *right)
      : m_label(label), m_left(new Node(left_label)), m_right(right) {
    m_left->m_parent = this;
    if (m_right)
      m_right->m_parent = this;
  }

  Node(char label, Node *left, char right_label)
      : m_label(label), m_left(left), m_right(new Node(right_label)) {
    m_right->m_parent = this;
    if (m_left)
      m_left->m_parent = this;
  }

  Node(char label, char left_label, char right_label)
      : m_label(label), m_left(new Node(left_label)),
        m_right(new Node(right_label)) {
    m_left->m_parent = this;
    m_right->m_parent = this;
  }

  char m_label;
  Node *m_left{nullptr};
  Node *m_right{nullptr};
  Node *m_parent{nullptr};
};

string label(Node *node) {
  return node == nullptr ? "(null)" : string(&node->m_label, 1);
}

template <typename N> class Iterator {
public:
  Iterator(N *root) : m_current(root) {
    while (m_current->m_left != nullptr)
      m_current = m_current->m_left;
  }

  Iterator() = default;

  Iterator &operator++() {
    if (m_current->m_right != nullptr) {
      m_current = m_current->m_right;
      while (m_current->m_left != nullptr)
        m_current = m_current->m_left;
    } else if (m_current->m_parent->m_left == m_current)
      m_current = m_current->m_parent;
    else if (m_current->m_parent->m_right == m_current) {
      do {
        m_current = m_current->m_parent;
      } while (m_current->m_parent != nullptr &&
               m_current->m_parent->m_right == m_current);
      m_current = m_current->m_parent;
    }
    // Past-the-end
    return *this;
  }
  bool operator==(const Iterator &other) {
    return m_current == other.m_current;
  }

  bool operator!=(const Iterator &other) { return !(*this == other); }

  char operator*() { return m_current->m_label; }

private:
  N *m_current{nullptr};
  N *m_previous{nullptr};
};

template <typename N> class PreorderIterator {
public:
  PreorderIterator(N *root) : m_current(root) {
    cout << "PreorderIterator() " << m_current << endl;
  }

  PreorderIterator() = default;

  PreorderIterator &operator++() {
    cout << "PreorderIterator::++ '" << string(1, m_current->m_label) << "' @ "
         << m_current << endl;
    if (m_current->m_left != nullptr)
      m_current = m_current->m_left;

    else if (m_current->m_right != nullptr)
      m_current = m_current->m_right;

    else if (m_current->m_parent != nullptr) {
      if (m_current->m_parent->m_left == m_current) {
        do
          m_current = m_current->m_parent;
        while (m_current != nullptr && m_current->m_right == nullptr);
        if (m_current != nullptr && m_current->m_right != nullptr)
          m_current = m_current->m_right;
      } else { // m_current->m_parent->m_right == m_current)
        cout << "RC" << endl;
        do {
          cout << "back up to " << string(1, m_current->m_label) << endl;
          m_current = m_current->m_parent;
        } while (m_current != nullptr && m_current->m_parent != nullptr &&
                 m_current->m_parent->m_left == m_current);
        cout << "backed up to " << string(1, m_current->m_label) << endl;
        if (m_current != nullptr && m_current->m_parent != nullptr &&
            m_current->m_parent->m_left == m_current) {
          cout << "not null" << endl;
          m_current = m_current->m_right;
          cout << "and down to " << string(1, m_current->m_label) << endl;
        }
        cout << "yeah m_current == " << m_current << endl;
      }
    }

    return *this;
  }
  bool operator==(const PreorderIterator &other) {
    return m_current == other.m_current;
  }

  bool operator!=(const PreorderIterator &other) { return !(*this == other); }

  char operator*() { return m_current->m_label; }

private:
  N *m_current{nullptr};
  N *m_previous{nullptr};
};

class Tree {
public:
  Tree(Node *root) : m_root(root) {}
  Iterator<Node> begin() { return Iterator<Node>(m_root); }
  Iterator<Node> end() { return Iterator<Node>(); }
  Node *root() const { return m_root; }

private:
  Node *m_root;
};

class PreorderTree {
public:
  PreorderTree(Tree tree) : m_tree(tree) {}

  PreorderIterator<Node> begin() {
    return PreorderIterator<Node>(m_tree.root());
  }

  PreorderIterator<Node> end() { return PreorderIterator<Node>(); }

private:
  Tree m_tree;
};

bool success{true};

enum class Direction { Inorder, Preorder };

string traverse(Node *root, Direction direction) {
  string res;
  switch (direction) {
  case Direction::Inorder: {
    Tree tree(root);
    for (char c : tree) {
      res.push_back(c);
    }
    return res;
  }
  case Direction::Preorder: {
    Tree tree(root);
    PreorderTree ptree(tree);
    for (char c : ptree) {
      res.push_back(c);
    }
    return res;
  }
  }
  return "xx";
}

bool failFast{true};

void check(Node *root, Direction direction, string answer) {
  static int runno{0};
  cout << "------- Run #" << ++runno << " ----------" << endl;
  auto res = traverse(root, direction);
  if (res != answer) {
    cout << "Incorrect for test#" << runno << " Expected " << answer << ", got "
         << res << "." << endl;
    success = false;
    if (failFast)
      exit(1);
  } else
    cout << "correct" << endl;
}

int main() {
  /*
          A
         / \
        B   D
         \
          C
  */
  Node *tree1 =
      new Node('A', new Node('B', nullptr, new Node('C')), new Node('D'));
  check(tree1, Direction::Inorder, "BCAD");
  check(tree1, Direction::Preorder, "ABCD");

  /*
          A
         / \
        B   D
       / \
      Z   C
  */
  Node *tree2 = new Node('A', new Node('B', 'Z', 'C'), new Node('D'));
  check(tree2, Direction::Inorder, "ZBCAD");
  check(tree2, Direction::Preorder, "ABZCD");

  /*
          A
           \
            D
             \
              E
  */
  auto tree3 = new Node('A', nullptr, new Node('D', nullptr, 'E'));
  check(tree3, Direction::Inorder, "ADE");
  check(tree3, Direction::Preorder, "ADE");

  /*
          A
         / \
        B   D
       /
      C
  */
  check(new Node('A', new Node('B', 'C', nullptr), new Node('D')),
        Direction::Inorder, "CBAD");

  /*
          A
         / \
        B   D
             \
              C
  */
  check(new Node('A', new Node('B'), new Node('D', nullptr, new Node('C'))),
        Direction::Inorder, "BADC");
  cout << (success ? "*** SUCCESS ***" : "*** FAILED ***") << endl;
}
