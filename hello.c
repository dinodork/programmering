#include <assert.h>
#include <stdio.h>
#include <string.h>

#define yywrap(yyscanner) (/*CONSTCOND*/ 1)

int main() {

  printf("Hello world %d!\n", yywrap(1));
  char apa[3];
  strcpy(apa, NULL);
}
