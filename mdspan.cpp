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

int main() {
  class Tree;
  using Node = std::variant<Tree *, std::string>;
  vraschle = 666;
  raketarsle = "kuken";

  visitoren v;
  v(1);
  v("pille");

  std::visit(v, vraschle);
  cout << "Hello world!" << endl;
}
