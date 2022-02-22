#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

template<typename V>
class Visitable {
public:
  virtual void accept( V &v ) = 0;
};

template<typename ... Vs>
class INode : public Vs ... {
};

template<typename ... Vs>
class Leaf : public INode<Vs ...> { 
public:
  explicit Leaf( const char *label ) : m_label( label ) {}

  using Vs::accept...;

  const char *m_label;
};

template<typename ... Vs>
class Parent : public INode<Vs ...> {

public:
  using NodeType = INode<Vs ...>;
  Parent(NodeType & lhs_arg, NodeType & rhs_arg)
    : m_lhs(lhs_arg), m_rhs(rhs_arg)
  {}

  NodeType & m_lhs, m_rhs;
};

// class PrintingVisitor : public IVisitor { 
// public:
//   void visit( Parent &plus ) { cout << " + "; }
//   void visit( Leaf &n ) { cout << n.m_label; }
// };

class TemplatedPrintingVisitor { 
public:
  using This = TemplatedPrintingVisitor;
  void visit( Parent<This> &plus ) { cout << " + "; }
  void visit( Leaf<This> &n ) { cout << n.m_label; }
};


class TemplatedNicePrintingVisitor { 
public:
  using This = TemplatedPrintingVisitor;
  void visit( Parent<This> &plus ) { cout << " * "; }
  void visit( Leaf<This> &n ) { cout << n.m_label; }
};

int main() {

  Leaf<TemplatedPrintingVisitor> a("A"), b("B");
//  Parent<TemplatedPrintingVisitor> p(a, b);

  TemplatedPrintingVisitor tpv;

  a.accept(tpv);
  cout << endl;
  cout << "---\n";

  b.accept(tpv);
  cout << endl;
  cout << "---\n";

  p.accept(tpv);
  cout << endl;
  cout << "---\n";
}
