#include <setjmp.h>
#include <stdio.h>

jmp_buf *jbp;

void a(int count) {
  printf("a(%d) called\n", count);
  longjmp(*jbp, count + 1); /* will return count+1 out of setjmp */
}

int main(void) {
  int count = 0; /* local vars must be volatile for setjmp */
  jmp_buf jump_buffer;
  jbp = &jump_buffer;
  if (setjmp(jump_buffer) != 3)
    a(count++);
}
