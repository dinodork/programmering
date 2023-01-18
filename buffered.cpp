#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;

int main() {

  std::basic_fstream<char> f("myfile.txt",
                             std::ios_base::out | std::ios_base::trunc);
  f << "xhoode";
//  f.flush();

  std::basic_fstream<char> fin("myfile.txt", std::ios_base::in);
  std::string s;
  fin >> s;
  cout << "Nu kommer jag " << s << endl;
}
