#include <cstdio>

extern "C" {
  int hello_from_c(int i);
}

int hello_from_c(int i) {
  printf("Hello from C! %i \n", i);
  return i * 2;
}
