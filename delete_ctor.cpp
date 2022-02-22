class My_class
{
private:
  My_class(const My_class &other) = delete;
  My_class &operator= (const My_class &other) = delete;
};

class A
{
public:
  A() {}
  A(const A &other);
};


int main()
{
//  My_class c;
  A a1;
  A a2(a1);
}
