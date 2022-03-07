#include <iostream>

using namespace std;

class DebugTracer {
public:
  DebugTracer(const char *fun, int line) : m_fun(fun) {
    std::cout << indent() << ">" << m_fun << " " << line << endl;
    m_indent += 2;
  }

  ~DebugTracer() {
    m_indent -= 2;
    std::cout << indent() << "<" << m_fun << endl;
  }

private:
  string indent() { return string(m_indent, ' '); }

  const char *m_fun;
  static int m_indent;
};

int DebugTracer::m_indent{0};

#define TRACE DebugTracer __(__FUNCTION__, __LINE__)

class Throwable {
public:
  Throwable() { cout << "Throwable #" << m_issue << endl; }
  Throwable(const Throwable &) {
    cout << "Throwable(const Throwable&) #" << m_issue << endl;
  }
  ~Throwable() { cout << "~Throwable #" << m_issue << endl; }

private:
  int m_issue{++m_current_issue};
  static int m_current_issue;
};

int Throwable::m_current_issue{0};

void bar(bool letsthrow) {
  TRACE;
  if (letsthrow)
    throw Throwable();
}

void foo(bool letsthrow) {
  TRACE;
  bar(letsthrow);
}

int main() {
  TRACE;
  try {
    foo(true);
  } catch (int i) {
    cout << "caught " << i << endl;
  } catch (const char *s) {
    cout << "caught " << s << endl;
  } catch (Throwable &&t) {
    cout << "caught a Throwable" << endl;
  }
}
