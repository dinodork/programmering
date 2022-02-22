#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>

#include <memory>

using std::cout;
using std::endl;

class Select_lex_unit;
class Select_lex_unit_owner {
public:
  void set_select_lex_unit(Select_lex_unit *new_slu);
  Select_lex_unit *select_lex_unit() const { return m_slu;  }
private:
  Select_lex_unit *m_slu{nullptr};
};

class Select_lex;
class Select_lex_owner {
public:
  void set_select_lex(Select_lex *new_sl);
  Select_lex *select_lex() const { return m_sl; }
private:
  Select_lex *m_sl{nullptr};
};

class Select_lex : public Select_lex_unit_owner, public Select_lex_owner {
public:
  Select_lex(std::string name) : m_name(name) {}
  Select_lex *next() { return select_lex(); }
  void set_owner(Select_lex_owner *new_owner) { prev = new_owner; }
  void unlink();
  void print() {
    cout << "[ ";
    for (auto sl = this; sl != nullptr; sl = sl->select_lex())
      cout << sl->m_name << ' ';
    cout << "]";
  }
private:
  std::string m_name;
  Select_lex_owner *prev{nullptr};
};

class Select_lex_unit : public Select_lex_owner, public Select_lex_unit_owner {
public:
  Select_lex_unit(std::string name) : m_name(name) {}
  Select_lex_unit *next() { return select_lex_unit(); }
  void set_owner(Select_lex_unit_owner *new_owner) { prev = new_owner; }
  void unlink();
  void print() {
    cout << "{ ";
    for (auto slu = this; slu != nullptr; slu = slu->select_lex_unit()) {
      cout << slu->m_name;
      select_lex()->print();
      cout << ' ';
    }
    cout << "}";
  }
private:  
  std::string m_name;
  Select_lex_unit_owner *prev{nullptr};
};

void Select_lex_owner::set_select_lex(Select_lex *new_sl) {
  m_sl = new_sl;
  m_sl->set_owner(this);
}

void Select_lex_unit_owner::set_select_lex_unit(Select_lex_unit *new_slu) {
  m_slu = new_slu;
  m_slu->set_owner(this);
}

void Select_lex::unlink() {
  if (prev != nullptr) prev->set_select_lex(next());
  if (next() != nullptr) next()->set_owner(prev);
}

void Select_lex_unit::unlink() {
  if (prev != nullptr) prev->set_select_lex_unit(next());
  if (next() != nullptr) next()->set_owner(prev);
}


int main()
{
//  foo(std::make_unique<const char[100]>());
  Select_lex a{"a"}, b{"b"}, c{"c"};
  b.set_select_lex(&c);
  a.set_select_lex(&b);

  Select_lex_unit slu_a{"slu_a"};
  slu_a.set_select_lex(&a);
  
  slu_a.print(); cout << endl;
  b.unlink();
  slu_a.print();

  Select_lex sl{"kalle"};

  cout << endl;
  cout << "Hello, world" << endl;
}
