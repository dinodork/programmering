#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class AvlTree {
  struct Node {
    Node(T t) : element(t) {}

    bool insert(T t, std::unique_ptr<Node> *parentPtr);

    void rotateLL(std::unique_ptr<Node> *parentPtr);
    void rotateRR(std::unique_ptr<Node> *parentPtr);
    void rotateRL(std::unique_ptr<Node> *parentPtr);
    void rotateLR(std::unique_ptr<Node> *parentPtr);

    int balance() { return get_height(left) - get_height(right); }

    void setHeight() {
      height = std::max(get_height(left), get_height(right)) + 1;
    }

    static int get_height(const std::unique_ptr<Node> &node) {
      if (node == nullptr)
        return 0;
      else
        return node->height;
    }

    T element;
    int height{0}; /// height of this tree
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

public:
  bool insert(T t) { return insert(&m_root, t, &m_root); }

  void print() {
    std::vector<Node *> queue;
    queue.push_back(m_root.get());
    print(&queue, 0, m_root->height);
  }

private:
  static bool insert(std::unique_ptr<Node> *node, T t,
                     std::unique_ptr<Node> *parentPtr) {
    if (*node == nullptr) {
      *node = std::make_unique<Node>(t);
      return t;
    } else
      return (*node)->insert(t, parentPtr);
  }

/**
                               _ nodePrintWidth
                              | |
                              v v
                               O
                             /   \
                            o     o
                           / \   / \
                          o   o o   o
                        | |     ^---^
                        | |       nodeSpacing
                        ^-^
                         node padding
                        ^-------------^
                            screenWidth

  We calculate the node padding as follows:
  - On the deepest level, the node padding is 0

  - On all other levels, we want the leftmost node centered between its two
    children. Hence the node padding is half the node spacing on the level
    below.
*/
  void print(std::vector<Node *> *queue, int currentDepth, int totalDepth) {
    if (queue->empty()) {
      cout << "queue empty" << endl;
      return;
    }
    bool any_children = false;
    const int maxScreenWidth = 60;
    const int nodePrintWidth = 7;

    if (nodePrintWidth * pow(2, totalDepth) > maxScreenWidth) {
      cout << "unprintable" << endl;
      return;
    }

    int screenWidth = pow(2, totalDepth) * nodePrintWidth;
    int nodePadding =
        currentDepth == totalDepth
            ? 0
            : screenWidth / (pow(2, currentDepth) + 1) - nodePrintWidth / 2;

    int nodeSpacing =
        (screenWidth - 2 * nodePadding) / (pow(2, currentDepth) - 1) -
        nodePrintWidth;

    for (int j = 0; j < nodePadding; ++j)
      cout << ' ';
    for (int i = 0; i < pow(2, currentDepth); ++i) {
      Node *node = queue->back();
      queue->pop_back();

      if (node->left == nullptr)
        queue->insert(queue->begin(), &nullnode);
      else {
        queue->insert(queue->begin(), node->left.get());
        any_children = true;
      }

      if (node->right == nullptr)
        queue->insert(queue->begin(), &nullnode);
      else {
        queue->insert(queue->begin(), node->right.get());
        any_children = true;
      }

      if (node == &nullnode)
        cout << "{_____}"; // std::string(nodePrintWidth, ' ');
      else
        cout << "{" << node->element << " h:" << node->height << "}";
      for (int j = 0; j < nodeSpacing; ++j)
        cout << ' ';
    }
    cout << endl << endl;
    if (any_children)
      print(queue, currentDepth + 1, totalDepth);
  }

  Node nullnode{-1};
  std::unique_ptr<Node> m_root;
};

template <typename T>
bool AvlTree<T>::Node::insert(T t,
                              std::unique_ptr<AvlTree<T>::Node> *parentPtr) {
  cout << "insert(" << t << ") @ " << element << endl;
  bool was_inserted = false;
  if (t > element)
    was_inserted = AvlTree::insert(&right, t, parentPtr);
  else if (t < element)
    was_inserted = AvlTree::insert(&left, t, parentPtr);

  if (!was_inserted)
    return false;

  setHeight();

  if (balance() < -1) {         // right-heavy
    if (right->balance() <= -1) // right-right-heavy
      rotateLL(parentPtr);
    else if (right->balance() >= 1) // right-left-heavy
      rotateRL(parentPtr);
  }
  return was_inserted;
}

template <typename T>
void AvlTree<T>::Node::rotateLL(std::unique_ptr<AvlTree<T>::Node> *parentPtr) {
  cout << "rotateLL @ " << element << endl;
  auto oldRoot = parentPtr->release();
  auto newRoot = right.release();
  oldRoot->right.reset(newRoot->left.release());
  newRoot->left.reset(oldRoot);
  parentPtr->reset(newRoot);

  oldRoot->setHeight();
  if (newRoot->right != nullptr)
    newRoot->right->setHeight();
  newRoot->setHeight();
}

template <typename T>
void AvlTree<T>::Node::rotateRL(std::unique_ptr<Node> *parentPtr) {
  cout << "rotateRL" << endl;
  auto oldRoot = parentPtr->release(); // = std::move(parentPtr) ?
  auto newRoot = right->left.release();

  auto rll_subtree = newRoot->left.release();
  auto rlr_subtree = newRoot->right.release();

  newRoot->left.reset(oldRoot);
  newRoot->right.reset(oldRoot->right.release());

  oldRoot->right.reset(rll_subtree);
  newRoot->right->left.reset(rlr_subtree);

  newRoot->left->setHeight();
  newRoot->right->setHeight();
  newRoot->setHeight();

  parentPtr->reset(newRoot);
}

int main() {
  {
    AvlTree<int> tree;
    tree.insert(6);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(5);
    tree.insert(7);
    tree.insert(9);
    tree.insert(4);
    tree.print();
    tree.insert(3);
    tree.print();
  }
  exit(0);
  {
    AvlTree<int> tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    tree.print();
  }

  {
    AvlTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.print();
  }
}
