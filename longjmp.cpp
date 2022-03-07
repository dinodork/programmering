#include <csetjmp>
#include <iostream>

using namespace std;

jmp_buf myjumpbuf;

struct A {
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }
};

void fum() {
  cout << "fum()" << endl;
  longjmp(myjumpbuf, 1);
}

void fie() {
  cout << "fie()" << endl;
  A a;
  fum();
}

void foo() {
  if (setjmp(myjumpbuf) == 1) {
    cout << "I jumped" << endl;
  } else {
    fie();
    cout << "I called fie()" << endl;
  }
}

int main() { foo(); }
