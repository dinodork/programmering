#include <iostream>
#include <string.h>

using std::cout;

template <class T, class U> class Lambda1 {
  T (*_f)(U);
  U _arg;
public:
  Lambda1(T (*f)(U), U arg) : _f(f), _arg(arg) {}
  Lambda1(T (*f)(U)) : _f(f) {}
  virtual T eval() { return _f(_arg); }
  virtual T eval(U u) { return _f(u); }
};

template <class T, class U, class V> class Lambda2 {

  T (*_f)(U, V);
  U _arg1;
  V _arg2;

public:
  Lambda2(T (*f)(U, V), U arg1, V arg2) :
    _f(f), _arg1(arg1), _arg2(arg2) {}

  Lambda2(T (*f)(U, V), U arg1) :
    _f(f), _arg1(arg1) {}

  Lambda2(T (*f)(U, V)) : _f(f) {}

  T eval() { return _f(_arg1, _arg2); }

  T eval(V arg2) { return _f(_arg1, arg2); }
};

template <class T>
class Wrapper {
public:
  const T value;
  Wrapper(T t) : value(t) {}  
};

template <class T> class ListIterator;

template <class T> class List {

  class ListCell {
  public:
    T * element;
    ListCell * next;
    ListCell(T * elementArg, ListCell * nextArg) : 
      element(elementArg), next(nextArg) {}
  };

  ListCell *first, *last;

public: 
  List<T> () : first(NULL), last(NULL) {}

  void add(T *element) {
    if (last == NULL)
    {
      first= new ListCell(element, NULL);
      last= first;
    }
    else
    {
      last->next = new ListCell(element, NULL);
      last= last->next;
    }
  }

  friend class ListIterator<T>;

};

template <class T, class U>
class Foreach : public Lambda1<T*, U*> {
  List<U> _list;
public:
  Foreach(T* (*f)(U*), List<U> list) : Lambda1<T*, U*>(f), _list(list) {}
  Foreach(T* (*f)(U*)              ) : Lambda1<T*, U*>(f)              {}

//  List<T> eval() { eval(_list); }

//  operator() { eval

  List<T> eval(const List<U>& list) {
    U *element;
    List<T> out;
    for (ListIterator<U> it(list); (element= it++);)
      out.add(_f(element));
    return out;
  }

};

template <class T, class U>
class Foreach2 : public Lambda1<T, U> {
  List<U> _list;
public:
  Foreach2(T (*f)(U), List<U> list) : Lambda1<T, U>(f), _list(list) {}
  Foreach2(T (*f)(U)              ) : Lambda1<T, U>(f)              {}

//  List<T> eval() { eval(_list); }

//  operator() { eval

  List<T> eval(const List<U>& list) {
    U *element;
    List<T> out;
    for (ListIterator<U> it(list); (element= it++);)
      out.add(&_f(*element));
    return out;
  }

};

template <class T> class ListIterator {

  typename List<T>::ListCell *_current;

public:
  ListIterator(const List<T> &list) : _current(list.first) {}
  T *operator++(int) {
    if (_current == NULL)
      return NULL;
    T *element = _current->element;
    _current = _current->next;
    return element;
  }
};

template <class T>
T plus(T a, T b) { return a + b; }

template <class T, class U>
Foreach<T, U> map(T* (*f)(U*)) {
  return Foreach<T, U>(f);
}


template <class T> Wrapper<T> * plus1(Wrapper<T> *a) { 
  return new Wrapper<T>(a->value + 1);
}

Wrapper<int> * plus1w(Wrapper<int> * a) {
  return new Wrapper<int>(a->value + 1);
}

int main() {

  int a = plus(10, 10);

  Lambda2 <int, int, int>plus10(&plus, 10);

//  Lambda< List<int> > add1toAll = map(&plus1);

  List< Wrapper<int> > l;
  l.add(new Wrapper<int>(1));
  l.add(new Wrapper<int>(2));
  l.add(new Wrapper<int>(3));

  cout << "list before: " << '\n';
  ListIterator< Wrapper<int> > li(l);
  while (Wrapper<int> *iw = li++)
    cout << "an int: " << iw->value << '\n';

  cout << "list after: " << '\n';
  Wrapper<int>*(*plus1iw)(Wrapper<int>*) = &plus1< int >;

  Foreach< Wrapper<int>, Wrapper<int> > fl(plus1iw);

  Foreach< Wrapper<int>, Wrapper<int> > add1ToAll = map(&plus1<int>);

  List< Wrapper<int> >newList = add1ToAll.eval(l);
  ListIterator< Wrapper<int> > li2(newList);
  while (Wrapper<int> *iw = li2++)
    cout << "an int: " << iw->value << '\n';

}
