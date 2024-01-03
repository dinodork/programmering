#include <functional>
#include <iostream>
#include <string>
#include <variant>

using std::cout;
using std::endl;

struct Leaf {
  std::string label;
};
struct Node;
using Tree = std::variant<Leaf, Node *>;
struct Node {
  Tree left, right;
};

template <typename... Ts> struct overload : Ts... {
  overload(Ts... ts) : Ts(ts)... {}
  using Ts::operator()...;
};

struct Overload1 {
  void operator()(const Leaf &) { cout << "visit(Leaf)\n"; }
  void operator()(const Node *) { cout << "visit(Node*)\n"; }
};

template <typename N, typename L> struct Overload2 : N, L {

  Overload2() = default;
  Overload2(N, L){};
  using N::operator();
  using L::operator();
};

int main() {

  Tree l1{Leaf{"a"}};
  Tree l2{Leaf{"b"}};
  Tree t1 = new Node{l1, l2};

  overload o{[&](const Leaf &) {}, [&](const Node *n) {}};

  overload<decltype(o)> ol{[&](const Leaf &) { cout << "visit(Leaf)\n"; },
                           [&](const Node *n) {
                             cout << "visit(Node*)\n";
                             std::visit(o, n->left);
                           }};

  o = ol;
  std::visit(ol, t1);

  cout << "Hello world!" << endl;
}
