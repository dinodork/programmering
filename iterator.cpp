#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <locale>
#include <unordered_map>
#include <typeinfo>

using std::cout;
using std::endl;

class ItrBase {
public:
  const char *m_name;
  ItrBase(const char *name = "anonymous") : m_name(name) {}

  virtual void  operator ++ () { cout << "ItrBase::++" ; }
  virtual const char * operator * () const { cout << "ItrBase::* : "; return m_name; }

protected:
  virtual bool equal(const ItrBase& o) const { return true; }
};


class ItrDesc : public ItrBase {
public:
  
  ItrDesc() = default;
  ItrDesc(const char *name) : ItrBase(name) {}
  const char * operator * () const override { cout << "ItrBase::* : "; return m_name; }
  void operator++() override { cout << "ItrDesc::++" ; }
};


int main()
{
  std::cout << "hello " << std::endl;

  ItrDesc barr[2] = { "foo", "fie" };
  ItrBase * ibp = barr;

  {
    cout << "Calling ++ on a sliced copy { ";
    ItrBase slicee = (*ibp);
    ++slicee;
    cout << " }" << endl;
  }
  {
    cout << "Calling * on a sliced copy { ";
    ItrBase slicee = (*ibp);
    *slicee;
    cout << " }" << endl;
  }
  cout << "Calling ++ on a dereferenced pointer { ";
  ++(*ibp);
  cout << " }" << endl;

}
