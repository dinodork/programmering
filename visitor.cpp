#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Plus;
class Number;
class IVisitor {
public:
  virtual void visit(Plus &plus) = 0;
  virtual void visit(Number &cn) = 0;
};

class Expression {
public:
  virtual void accept(IVisitor &v) = 0;
  virtual void acceptAndPrint(IVisitor &v) = 0;
};

class Plus : public Expression {
public:
  Plus(Expression &lhs_arg, Expression &rhs_arg) : lhs(lhs_arg), rhs(rhs_arg) {}

  virtual void accept(IVisitor &v) {
    lhs.accept(v);
    v.visit(*this);
    rhs.accept(v);
  }

  void acceptAndPrint(IVisitor &v) override {
    lhs.accept(v);
    cout << " * ";
    rhs.accept(v);
  }

  Expression &lhs, &rhs;
};

class Number : public Expression {
public:
  int value;

  Number(int v) : value(v) {}
  virtual void accept(IVisitor &v) { v.visit(*this); }

  void acceptAndPrint(IVisitor &v) override { cout << value; }
};

class PrintingVisitor : public IVisitor {
public:
  void visit(Plus &plus) { cout << " + "; }
  void visit(Number &n) { cout << n.value; }
};

int main() {

  Number a(13), b(7);
  Plus p(a, b);

  PrintingVisitor pv;

  p.accept(pv);
  cout << endl;
  cout << "---\n";

  p.acceptAndPrint(pv);
  cout << endl;
  cout << "---\n";
}
