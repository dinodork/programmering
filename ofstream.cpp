#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

int main() {
  cout << "Pitt!" << endl;
  std::basic_ofstream<char> stream;
  stream.open("filename", std::ios_base::in | std::ios_base::out );
  cout << "fejlbitt " << (stream.rdstate() | std::ios_base::failbit) << endl;
//  stream.exceptions(std::ifstream::failbit);
  cout << "pung!" << endl;
//  stream.clear();
//  stream.close();
  stream.open("filename", std::ios_base::in | std::ios_base::out |std::ios_base::app);
  cout << "arsel!" << endl;
  cout << "rdstejt " << stream.rdstate() << endl;
  cout << "ekseptjens " << stream.exceptions() << endl;
  cout << "fejlbitt " << (stream.rdstate() | std::ios_base::failbit) << endl;
  stream.write("kuken\n", 6);
}


