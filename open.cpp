#include <unistd.h>
#include <iostream>
#include <fcntl.h>

using std::cout;
using std::endl;

int main() {
  cout << "Pitt!" << endl;
  auto handle = open("filename", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
  cout << "handel " << handle << endl;
  handle = open("filename", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
  cout << "handel " << handle << endl;

  write(handle, "kuken\n", 6);
}


