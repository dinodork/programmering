#include <assert.h>
#include <stdio.h>
#include <string.h>

#define dr(x, cell) ((struct cell *)doid(x)) /* Dereference object handle */

INLINE struct listcell *doid(ohandle x) /* Generic object dereferencing */
{
  return (struct listcell *)(begin_image + x);
}

typedef unsigned char objtype;   /* Type identifier */
typedef unsigned char objrefcnt; /* Reference counter */
typedef struct objtags_rec {
  objtype ttag;
  objrefcnt rcnt;
} objtags;

#define HEADFILLER short int filler

#define LONGINT long long

struct integercell {
  objtags tags;
  HEADFILLER;
  union {
    char data[8];
    LONGINT i;
  };
};

int main() {

  objtags ot = {'a', 'b'};
  struct integercell ic = {ot, 0, "abcdefgh"};

#define getinteger(h) (dr(h, integercell)->i)

  long long int i = getinteger(
}
