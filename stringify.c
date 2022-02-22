#include <assert.h>
#include <stdio.h>

int main() {

  printf("hej bajs\n");

  printf("Hej din %c \n", ((const char *)"apa")[-1]);
  assert("apa"[0] == 'a');
  assert("apa"[1] == 'p');
  assert("apa" + 1 == 'a');
}
