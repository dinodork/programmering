#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int main() {
  auto filename = "mapp/minfil.txt";
  if (FILE *f = std::fopen(filename, "rw")) {
    if (!f) {
      boost::system::error_code ec;
      boost::filesystem::create_directories(
          boost::filesystem::path{"mapp"}.parent_path(), ec);
      if (ec) {
        cout << "failed to create directory" << endl;
        return 1;
      }
    } else
      cout << "open successful" << endl;
    std::vector<char> buf(10);
    auto seek_status = std::fseek(f, 1, SEEK_SET);
    if (seek_status)
      cout << "seek failed " << endl;
    auto nread =
        std::fread(&buf[0], sizeof(decltype(buf)::value_type), buf.size(), f);
    cout << "Read " << nread << " bytes" << endl;
    cout << "File contains: '";
    for (char c : buf)
      cout << c;
    cout << "'" << endl;
  } else {
    cout << "failed to open " << filename << "." << endl;
  }
}
