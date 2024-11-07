#include <iostream>
#include <variant>

using namespace std;

using Literal = std::variant<int, float, string>;

struct BinaryExpr;
using Expr = variant<Literal, BinaryExpr>;

struct BinaryExpr {
  string op;
  Expr *lhs, *rhs;
};

template <typename... Callable> struct visitor : Callable... {
  using Callable::operator()...;
  // Deduction guide
  visitor(Callable... cs) : Callable(cs)... {}
};

template <typename... Callable> class BinaryExprVisitor : public Callable... {
public:
  using Callable::operator()...;
  // Deduction guide
  BinaryExprVisitor(Callable... cs) : Callable(cs)... {}

  void operator()(BinaryExpr be) { visit(be); }

  void visit(BinaryExpr be) {
    std::visit(*this, *be.lhs);
    cout << " " << be.op << " ";
    std::visit(*this, *be.rhs);
    cout << endl;
  }
};

int main() {
  Literal l1{"theliteral"};
  Literal l2{123};
  Expr e1(l1);
  Expr e2(l2);

  visit(visitor{[](string s) { cout << "s'" << s << "'\n"; },
                [](int s) { cout << "i" << s << "\n"; },
                [](float s) { cout << "f" << s << "\n"; }},
        l1);

  BinaryExpr be{"+", &e1, &e2};
  Expr e{be};

  visitor literalv{[](string s) { cout << "s'" << s << "'"; },
                   [](int s) { cout << "i" << s << "\n"; },
                   [](float s) { cout << "f" << s << "\n"; }};

  visitor exprv{[literalv](Literal l) { visit(literalv, l); },
                [](BinaryExpr be) { cout << "binop\n"; }};

  visit(visitor{[](Literal l) { cout << "literal\n"; },
                [exprv](BinaryExpr be) {
                  visit(exprv, *be.lhs);
                  cout << " " << be.op << " ";
                  visit(exprv, *be.rhs);
                }},
        e);

  cout << "class-based recursion:\n";
  cout << "----------------------\n";
  BinaryExprVisitor bev{
      [literalv](Literal l) { visit(literalv, l); },
  };
  visit(bev, e);
  {
    cout << "Univisitor:\n";
    cout << "-----------\n";
    visitor univisitor{literalv, exprv};
    visit(univisitor, e);
  }
}
