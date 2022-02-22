#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Product {
public:
};

class ProductA : public Product {
public:
  ProductA(int a) { cout << "ProductA::ProductA" << endl; }
};

class ProductB : public Product {
public:
  ProductB(int a, int b) { cout << "ProductB::ProductB" << endl; }
};

template<typename T, typename ...Args>
auto make(Args ...args) {
  return new T(args...);
}

int main() {
  Product *p = make<ProductA>(1);
  Product *w = make<ProductB>(1, 2);
}
