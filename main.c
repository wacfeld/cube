#include <stdio.h>
// #include <assert.h>
// #include <ctype.h>
// #include <errno.h>
// #include <float.h>
// #include <limits.h>
// #include <locale.h>
// #include <math.h>
// #include <setjmp.h>
// #include <signal.h>
// #include <stdarg.h>
// #include <stddef.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
#define putd(x) printf(#x ": %d\n", x)

typedef struct
{
  char ctr;
  char ring[8];
  char **adj;
} Face;

int main()
{
  Face U = {'y', {[0 ... 7] = 'y'}};
  Face D = {'w', {[0 ... 7] = 'w'}};
  Face F = {'o', {[0 ... 7] = 'o'}};
  Face B = {'r', {[0 ... 7] = 'r'}};
  Face R = {'b', {[0 ... 7] = 'b'}};
  Face L = {'g', {[0 ... 7] = 'g'}};

  U.adj = (char *[]) {B.ring+0, R.ring+0, F.ring+0, L.ring+0};
  D.adj = (char *[]) {F.ring+4, R.ring+4, B.ring+4, L.ring+4};
  F.adj = (char *[]) {U.ring+4, R.ring+6, D.ring+0, L.ring+2};
  B.adj = (char *[]) {U.ring+0, L.ring+6, D.ring+4, R.ring+2};
  R.adj = (char *[]) {U.ring+2, B.ring+6, D.ring+2, F.ring+2};
  L.adj = (char *[]) {U.ring+6, F.ring+6, D.ring+6, B.ring+2};

  
}
