#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {

  int i = 1;
outer_loop:

  int j = 1;
inner_loop:

  printf("%i\t%i\n", i, j);

  if (++i <= 10)
    goto outer_loop;
  if (++j <= 10)
    goto inner_loop;
}
