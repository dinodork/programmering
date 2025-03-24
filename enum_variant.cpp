#include <iostream>

using std::cout, std::endl;

int main() {

  struct Plus {};
  struct Minus {};
  struct Like {
    char escape;
  };

  using binop = std::variant<Plus, Minus, Like>;

  binop b1(Plus{});
  binop b2(Like{'\n'});

  if (std::holds_alternative<Like>(b2)) {
    char escape = std::get<Like>(b2).escape;
    cout << "Escape '" << escape << "'" << endl;
  }
}
