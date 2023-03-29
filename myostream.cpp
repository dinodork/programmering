#include <fstream>
#include <iostream>

class myofstream {

public:
  void open(const char *filename) { thestream.open(filename); }
  void close() {
    std::cout << "Closing. Wrote " << writeCount << " bytes." << std::endl;
    thestream.close(); }

  myofstream &operator<<(const void *__p) {
    std::cout << "Wirting oid" << std::endl;
    thestream << __p;
    return *this;
  }

  myofstream& operator<<(short n) {
    writeCount += n;
    thestream << n;
    return *this;
  }
/*
  myofstream& operator<<(std::ofstream& (*pf)(std::ofstream&))
  {
    return *this;
  }
*/

  friend myofstream& operator<<(myofstream& ms, const char *str);
private:
  size_t writeCount{0};
  std::ofstream thestream;
};

myofstream& operator<<(myofstream& ms, const char *str) {
  ms.writeCount += strlen(str);
  ms.thestream << str;
  return ms;
}

int main() {

  std::ofstream orgiefil;
  orgiefil.open("pungfil.txt");
  orgiefil << "a" << 'b' << 6 << std::endl;
  
  myofstream myfile;
  myfile.open("kukfil.txt");
  myfile << "Hej" << "kuk" << 4;
//  myfile << "och pung!";
  myfile.close();
}
