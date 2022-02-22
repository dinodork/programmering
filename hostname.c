#include <stdio.h>
#include <unistd.h>

int main() {

  printf("hej bajs\n");

  char hostname[1000];
  int res = gethostname(hostname, 1000);
  printf("The hostname is %s res %i\n", hostname, res);
}
