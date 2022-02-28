#include <iostream>
#include <string.h>
using std::cout;

class Visitor;
class ConstVisitor;
// class AbstractVisitorWrapper;

class Node {
public:
  virtual void accept(Visitor &v) = 0;
  virtual void accept(ConstVisitor &v) const = 0;
  //  virtual void acceptWrapper( AbstractVisitorWrapper v ) const;
};

class CompositeNode;
class BiNode;
class ANode;
class BNode;

class Visitor {
public:
  void visit(CompositeNode *cn) { cout << "A CompositeNode\n"; }
  void visit(BiNode *cn) { cout << "A BiNode\n"; }
  void visit(ANode *an) { cout << "An ANode\n"; }
  void visit(BNode *bn) { cout << "A BNode\n"; }
};

class ConstVisitor {
public:
  void visit(const CompositeNode *cn) { cout << "A const CompositeNode\n"; }
  void visit(const BiNode *cn) { cout << "A BiNode\n"; }
  void visit(const ANode *an) { cout << "A const ANode\n"; }
  void visit(const BNode *bn) { cout << "A const BNode\n"; }
};

template <class T> class VisitorWrapper {
  Visitor *_v;
  ConstVisitor *_cv;

public:
  VisitorWrapper(Visitor &v) : _v(&v), _cv(NULL) {}
  VisitorWrapper(ConstVisitor &cv) : _v(NULL), _cv(&cv) {}
  void invokeAccept(const Node *node) {
    if (_v == NULL)
      node->accept(*_cv);
    else
      const_cast<Node *>(node)->accept(*_v);
  }
  void invokeVisit(const T *node) {
    if (_v == NULL)
      _cv->visit(node);
    else
      _v->visit(const_cast<T *>(node));
  }
};

class CompositeNode : public Node {
public:
  Node *nodes[3];
  void accept(Visitor &v) { acceptWrapper(v); }
  void accept(ConstVisitor &v) const { acceptWrapper(v); }
  void acceptWrapper(VisitorWrapper<CompositeNode> wrapper) const {
    wrapper.invokeAccept(nodes[0]);
    wrapper.invokeAccept(nodes[1]);
    wrapper.invokeAccept(nodes[2]);
    wrapper.invokeVisit(this);
  }
};

class BiNode : public Node {
public:
  Node *nodes[2];
  void accept(Visitor &v) { acceptWrapper(v); }
  void accept(ConstVisitor &v) const { acceptWrapper(v); }
  void acceptWrapper(VisitorWrapper<BiNode> wrapper) const {
    wrapper.invokeAccept(nodes[0]);
    wrapper.invokeAccept(nodes[1]);
    wrapper.invokeVisit(this);
  }
};
class ANode : public Node {
  void accept(Visitor &v) { v.visit(this); }
  void accept(ConstVisitor &v) const { v.visit(this); }
};

class BNode : public Node {
  void accept(Visitor &v) { v.visit(this); }
  void accept(ConstVisitor &v) const { v.visit(this); }
};

int main() {

  CompositeNode cn;
  BiNode bn;
  bn.nodes[0] = new ANode;
  bn.nodes[1] = new BNode;

  cn.nodes[0] = new ANode;
  cn.nodes[1] = &bn;
  cn.nodes[2] = new ANode;

  Visitor v;
  ((Node *)&cn)->acceptWrapper(v);

  cout << "---\n";

  ConstVisitor cv;
  cn.acceptWrapper(cv);
}
