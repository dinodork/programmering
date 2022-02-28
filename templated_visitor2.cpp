#include <iostream>
#include <string.h>
#include <utility>

using std::cout;
using std::endl;

template <typename V, typename... Vs> class Leaf;

template <typename V> class NonLeaf;

template <typename VT> class Visitable {
public:
  using VisitorType = VT;
  virtual void accept(VisitorType &&vt) = 0;
};

/*
template<typename V, typename ... Vs>
class MultiVisitable : V {
public:
  MultiVisitable<Vs...> others;
};
*/
class Printer {
public:
  using TheVisitable = Visitable<Printer>;
  void visit(Leaf<TheVisitable> &leaf);
  void visit(NonLeaf<TheVisitable> &leaf);
};

class ReversePrinter {
public:
  using TheVisitable = Visitable<Printer>;
  void visit(Leaf<TheVisitable> &leaf);
  void visit(NonLeaf<TheVisitable> &leaf);
};

template <typename... V> class Node : public V... {
  //  using VisitorType = typename V::VisitorType;
};

template <typename V> class NonLeaf : public Node<V> {
public:
  using VisitorType = typename V::VisitorType;
  void accept(VisitorType &&vt) override {
    m_left->accept(std::forward<VisitorType>(vt));
    vt.visit(*this);
    m_right->accept(std::forward<VisitorType>(vt));
  }
  NonLeaf(Node<V> *left, Node<V> *right) : m_left(left), m_right(right) {}

  Node<V> *m_left, *m_right;
};

template <typename V> class LeafAcceptor : public Node<V> {
  using VisitorType = typename V::VisitorType;
  void accept(VisitorType &&vt) override { vt.visit(*this); }
};

template <typename... LeafAcceptors> class Leaf : public LeafAcceptors... {
public:
  Leaf(std::string &&label) : m_label(label) {}
  const std::string &label() { return m_label; }
  std::string m_label;
};

void Printer::visit(Leaf<TheVisitable> &leaf) { cout << leaf.label(); }
void Printer::visit(NonLeaf<TheVisitable> &nl) { cout << ", "; }
void ReversePrinter::visit(Leaf<TheVisitable> &leaf) { cout << leaf.label(); }
void ReversePrinter::visit(NonLeaf<TheVisitable> &nl) { cout << ", "; }

int main() {

  using Leaf = Leaf<Visitable<Printer>, Visitable<ReversePrinter>>;
  //  using NonLeaf = NonLeaf<Visitable<Printer>, Visitable<ReversePrinter>;
  Leaf left{"left"};
  Leaf right{"right"};
  NonLeaf nl(&left, &right);
  nl.accept(Printer());
  cout << endl;
}
