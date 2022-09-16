#include <stdio.h>
// #include <assert.h>
#include <ctype.h>
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

// cube {{{1
typedef struct
{
  char ctr;
  char ring[8];
  char *(*adj)[3];
} Face;

Face U = {'y', {[0 ... 7] = 'y'}};
Face D = {'w', {[0 ... 7] = 'w'}};
Face F = {'o', {[0 ... 7] = 'o'}};
Face B = {'r', {[0 ... 7] = 'r'}};
Face R = {'b', {[0 ... 7] = 'b'}};
Face L = {'g', {[0 ... 7] = 'g'}};

void triplecpy(char *dest[3], char *src[3])
{
  *dest[0] = *src[0];
  *dest[1] = *src[1];
  *dest[2] = *src[2];
}

void cwturn(Face *f)
{
  char *r = f->ring;
  char tmp = r[0];
  r[0] = r[6];
  r[6] = r[4];
  r[4] = r[2];
  r[2] = tmp;
  r[1] = r[7];
  r[7] = r[5];
  r[5] = r[3];
  r[3] = tmp;

  char pmet[3];
  char *temp[3] = {pmet+0, pmet+1, pmet+2};

  char *(*a)[3] = f->adj;
  
  triplecpy(temp, a[0]);
  triplecpy(a[0], a[3]);
  triplecpy(a[3], a[2]);
  triplecpy(a[2], a[1]);
  triplecpy(a[1], temp);
}

// void ccwturn(Face *f)
// {
  
// }

// void doalg(char *alg)
// {
//   while(alg)
//   {
//     if(*alg == 'u')
//   }
// }

// cube IO {{{1
#define bufy 11
#define bufx 15
#define COLOR 1

void printface(Face *f, int off, char (*buf)[15], int y, int x)
{
  static char yxs[8][2] = {
    {0, 0},
    {0, 1},
    {0, 2},
    {1, 2},
    {2, 2},
    {2, 1},
    {2, 0},
    {1, 0},
  };
  
  char *r = f->ring;
  for(int i = 0; i < 8; i++)
  {
    buf[y + yxs[i][0]][x + yxs[i][1]] = r[(off + i) % 8];
  }

  buf[y+1][x+1] = f->ctr;
}

char *color(char c)
{
  if(c == 'r') return "\x1b[31m#\x1b[0m";
  if(c == 'g') return "\x1b[32m#\x1b[0m";
  if(c == 'y') return "\x1b[35m#\x1b[0m";
  if(c == 'b') return "\x1b[34m#\x1b[0m";
  if(c == 'w') return "\x1b[37m#\x1b[0m";
  if(c == 'o') return "\x1b[36m#\x1b[0m";
  
  else return " ";
}

void printcube()
{
  puts("---------------");
  static char buf[bufy][bufx] = {[0 ... bufy-1] = {[0 ... bufx-1] = ' '}};
  
  printface(&B, 4, buf, 0, 4);
  printface(&L, 6, buf, 4, 0);
  printface(&U, 0, buf, 4, 4);
  printface(&R, 2, buf, 4, 8);
  printface(&D, 4, buf, 4, 12);
  printface(&F, 0, buf, 8, 4);

  for(int y = 0; y < bufy; y++)
  {
    for(int x = 0; x < bufx; x++)
    {
      if(COLOR)
        printf("%s", color(buf[y][x]));
      else
        putchar(toupper(buf[y][x]));
    }
    putchar('\n');
  }

}

// main {{{1

int main()
{
  U.adj = (char *[4][3]) {{B.ring+0,B.ring+1,B.ring+2}, {R.ring+0,R.ring+1,R.ring+2}, {F.ring+0,F.ring+1,F.ring+2}, {L.ring+0,L.ring+1,L.ring+2}};
  D.adj = (char *[4][3]) {{F.ring+4,F.ring+5,F.ring+6}, {R.ring+4,R.ring+5,R.ring+6}, {B.ring+4,B.ring+5,B.ring+6}, {L.ring+4,L.ring+5,L.ring+6}};
  F.adj = (char *[4][3]) {{U.ring+4,U.ring+5,U.ring+6}, {R.ring+6,R.ring+7,R.ring+0}, {D.ring+0,D.ring+1,D.ring+2}, {L.ring+2,L.ring+3,L.ring+4}};
  B.adj = (char *[4][3]) {{U.ring+0,U.ring+1,U.ring+2}, {L.ring+6,L.ring+7,L.ring+0}, {D.ring+4,D.ring+5,D.ring+6}, {R.ring+2,R.ring+3,R.ring+4}};
  R.adj = (char *[4][3]) {{U.ring+2,U.ring+3,U.ring+4}, {B.ring+6,B.ring+7,B.ring+0}, {D.ring+2,D.ring+3,D.ring+4}, {F.ring+2,F.ring+3,F.ring+4}};
  L.adj = (char *[4][3]) {{U.ring+6,U.ring+7,U.ring+0}, {F.ring+6,F.ring+7,F.ring+0}, {D.ring+6,D.ring+7,D.ring+0}, {B.ring+2,B.ring+3,B.ring+4}};

  printcube();
  cwturn(&D);
  cwturn(&D);
  cwturn(&D);
  printcube();
}
