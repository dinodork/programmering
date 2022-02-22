#include <iostream>
#include <cstring>


using std::cout;
using std::endl;


template <typename T1, typename T2>
T1 read_unaligned(T2 address) {
  T1 t;
  memcpy(&t, address, sizeof(T1));
  return t;
}

template<>
char *read_unaligned<char*,char*>(char * address);

template <typename T1, typename T2>
void write_unaligned(T1 value, T2 address) {
  memcpy(address, &value, sizeof(T1));
}

int main()
{
  char buf[20];
  char *location = buf + 2;
  cout << "hej" << endl;
//  *((int*)location) = 666;
  write_unaligned(666, buf + 2);
  cout << "apa" << endl;
  int i = read_unaligned<int>(buf + 2);
  cout << i << " kaka" << endl;


  int apa = 1234;
  write_unaligned(&apa, buf + 7);
  cout << "fjo" << endl;
  int *bepa = read_unaligned<int*>(buf + 7);
  cout << *bepa << endl;

  const char *k = "reka";
  char **location2 = (char**)(buf + 11);
  cout << "assajna" << endl;
//  *location2 = (char*)k;
  write_unaligned(k, buf + 11);
  cout << "nu sa ska vi runka" << endl;
//  cout << *((char**)(buf + 11)) << endl;
  cout << read_unaligned<char*>(buf + 11) << endl;
}
