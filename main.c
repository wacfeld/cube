#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define putd(x) printf(#x ": %d\n", x)

#include "queue.h"

// cube {{{1
typedef struct
{
  char ctr;
  char ring[8];
  char *(*adj)[3];
} Face;

typedef struct
{
  Face *U, *D, *F, *B, *R, *L;
} cube;

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
  tmp = r[1];
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

void ccwturn(Face *f)
{
  char *r = f->ring;
  char tmp = r[0];
  r[0] = r[2];
  r[2] = r[4];
  r[4] = r[6];
  r[6] = tmp;
  tmp = r[1];
  r[1] = r[3];
  r[3] = r[5];
  r[5] = r[7];
  r[7] = tmp;
  char pmet[3];
  char *temp[3] = {pmet+0, pmet+1, pmet+2};

  char *(*a)[3] = f->adj;
  
  triplecpy(temp, a[0]);
  triplecpy(a[0], a[1]);
  triplecpy(a[1], a[2]);
  triplecpy(a[2], a[3]);
  triplecpy(a[3], temp);
}

void doqt(cube *cb, char t)
{
    if(t == 'u') ccwturn(cb->U);
    else if(t == 'd') ccwturn(cb->D);
    else if(t == 'f') ccwturn(cb->F);
    else if(t == 'b') ccwturn(cb->B);
    else if(t == 'r') ccwturn(cb->R);
    else if(t == 'l') ccwturn(cb->L);
    
    else if(t == 'U') cwturn(cb->U);
    else if(t == 'D') cwturn(cb->D);
    else if(t == 'F') cwturn(cb->F);
    else if(t == 'B') cwturn(cb->B);
    else if(t == 'R') cwturn(cb->R);
    else if(t == 'L') cwturn(cb->L);
    
    else if(t == '0') cwturn(cb->U), cwturn(cb->U);
    else if(t == '1') cwturn(cb->D), cwturn(cb->D);
    else if(t == '2') cwturn(cb->F), cwturn(cb->F);
    else if(t == '3') cwturn(cb->B), cwturn(cb->B);
    else if(t == '4') cwturn(cb->R), cwturn(cb->R);
    else if(t == '5') cwturn(cb->L), cwturn(cb->L);
}

void undoqt(cube *cb, char t)
{
    if(t == 'U') ccwturn(cb->U);
    else if(t == 'D') ccwturn(cb->D);
    else if(t == 'F') ccwturn(cb->F);
    else if(t == 'B') ccwturn(cb->B);
    else if(t == 'R') ccwturn(cb->R);
    else if(t == 'L') ccwturn(cb->L);
    
    else if(t == 'u') cwturn(cb->U);
    else if(t == 'd') cwturn(cb->D);
    else if(t == 'f') cwturn(cb->F);
    else if(t == 'b') cwturn(cb->B);
    else if(t == 'r') cwturn(cb->R);
    else if(t == 'l') cwturn(cb->L);
    
    else if(t == '0') cwturn(cb->U), cwturn(cb->U);
    else if(t == '1') cwturn(cb->D), cwturn(cb->D);
    else if(t == '2') cwturn(cb->F), cwturn(cb->F);
    else if(t == '3') cwturn(cb->B), cwturn(cb->B);
    else if(t == '4') cwturn(cb->R), cwturn(cb->R);
    else if(t == '5') cwturn(cb->L), cwturn(cb->L);
}

void doalg(cube *cb, char *alg)
{
  while(*alg)
  {
    doqt(cb, *alg);
    
    alg++;
  }
}

void undoalg(cube *cb, char *alg)
{
  char *a = alg + strlen(alg);
  do
  {
    a--;
    
    undoqt(cb, *a);
    
  } while(a != alg);
}

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
  else if(c == 'g') return "\x1b[32m#\x1b[0m";
  else if(c == 'y') return "\x1b[35m#\x1b[0m";
  else if(c == 'b') return "\x1b[34m#\x1b[0m";
  else if(c == 'w') return "\x1b[37m#\x1b[0m";
  else if(c == 'o') return "\x1b[36m#\x1b[0m";
  
  else return " ";
}

void printcube(cube *cb)
{
  puts("---------------");
  static char buf[bufy][bufx] = {[0 ... bufy-1] = {[0 ... bufx-1] = ' '}};
  
  printface(cb->B, 4, buf, 0, 4);
  printface(cb->L, 6, buf, 4, 0);
  printface(cb->U, 0, buf, 4, 4);
  printface(cb->R, 2, buf, 4, 8);
  printface(cb->D, 4, buf, 4, 12);
  printface(cb->F, 0, buf, 8, 4);

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

// // solving {{{1

#define test(stat) {if(!(stat)) return 0;}
int dcross(cube *cb)
{
  char col = cb->D->ctr;
  
  test(cb->D->ring[1] == col);
  test(cb->D->ring[3] == col);
  test(cb->D->ring[5] == col);
  test(cb->D->ring[7] == col);
  
  test(cb->F->ring[5] == cb->F->ctr);
  test(cb->B->ring[5] == cb->B->ctr);
  test(cb->R->ring[5] == cb->R->ctr);
  test(cb->L->ring[5] == cb->L->ctr);

  return 1;
}

char moveface(char move)
{
  if(move == 'u' || move == 'U' || move == '0') return 'u';
  else if(move == 'd' || move == 'D' || move == '1') return 'd';
  else if(move == 'f' || move == 'F' || move == '2') return 'f';
  else if(move == 'b' || move == 'B' || move == '3') return 'b';
  else if(move == 'r' || move == 'R' || move == '4') return 'r';
  else if(move == 'l' || move == 'L' || move == '5') return 'l';

  return 0;
}

void dfs(cube *cb, int (*goal)(cube *cb), int maxdepth)
{
  void dfshelp(cube *cb, int (*goal)(cube *cb), int maxdepth, char prev, char *ans, int ai, int *record);
  
  char *ans = malloc(maxdepth+1);
  
  int record = maxdepth+1;
  dfshelp(cb, goal, maxdepth, 0, ans, 0, &record);
  // if(dfshelp(cb, goal, maxdepth, 0, ans))
  // {
  //   return ans;
  // }

  // else
  // {
  //   free(ans);
  //   return NULL;
  // }
  free(ans);
}

void dfshelp(cube *cb, int (*goal)(cube *cb), int maxdepth, char prev, char *ans, int ai, int *record)
{
  static char moves[] = "udfbrlUDFBRL012345";
  static char faces[] = "udfbrludfbrludfbrl";

  if(goal(cb))
  {
    ans[ai] = 0;
    if(ai < *record)
    {
      puts(ans);
      *record = ai;
    }
    return;
    // return 1;
  }

  if(maxdepth <= 0)
    // return 0;
    return;
  
  char prevface = moveface(prev);
  for(int i = 0; moves[i]; i++)
  {
    if(faces[i] == prevface) continue;

    ans[ai] = moves[i];
    doqt(cb, moves[i]);
    // int res = dfshelp(cb, goal, maxdepth-1, moves[i], ans+1);
    dfshelp(cb, goal, maxdepth-1, moves[i], ans, ai+1, record);
    undoqt(cb, moves[i]);

    // if(res)
    // {
    //   *ans = moves[i];
    //   return 1;
    // }
  }

  // return 0;
  return;
}

// main {{{1

#define BUFMAX 1000

int main(int argc, char **argv)
{
  Face U = {'y', {[0 ... 7] = 'y'}};
  Face D = {'w', {[0 ... 7] = 'w'}};
  Face F = {'o', {[0 ... 7] = 'o'}};
  Face B = {'r', {[0 ... 7] = 'r'}};
  Face R = {'b', {[0 ... 7] = 'b'}};
  Face L = {'g', {[0 ... 7] = 'g'}};
  
  U.adj = (char *[4][3]) {{B.ring+0,B.ring+1,B.ring+2}, {R.ring+0,R.ring+1,R.ring+2}, {F.ring+0,F.ring+1,F.ring+2}, {L.ring+0,L.ring+1,L.ring+2}};
  D.adj = (char *[4][3]) {{F.ring+4,F.ring+5,F.ring+6}, {R.ring+4,R.ring+5,R.ring+6}, {B.ring+4,B.ring+5,B.ring+6}, {L.ring+4,L.ring+5,L.ring+6}};
  F.adj = (char *[4][3]) {{U.ring+4,U.ring+5,U.ring+6}, {R.ring+6,R.ring+7,R.ring+0}, {D.ring+0,D.ring+1,D.ring+2}, {L.ring+2,L.ring+3,L.ring+4}};
  B.adj = (char *[4][3]) {{U.ring+0,U.ring+1,U.ring+2}, {L.ring+6,L.ring+7,L.ring+0}, {D.ring+4,D.ring+5,D.ring+6}, {R.ring+2,R.ring+3,R.ring+4}};
  R.adj = (char *[4][3]) {{U.ring+2,U.ring+3,U.ring+4}, {B.ring+6,B.ring+7,B.ring+0}, {D.ring+2,D.ring+3,D.ring+4}, {F.ring+2,F.ring+3,F.ring+4}};
  L.adj = (char *[4][3]) {{U.ring+6,U.ring+7,U.ring+0}, {F.ring+6,F.ring+7,F.ring+0}, {D.ring+6,D.ring+7,D.ring+0}, {B.ring+2,B.ring+3,B.ring+4}};

  cube temp = {&U,&D,&F,&B,&R,&L};
  cube *cb = &temp;

  char buf[BUFMAX];

  printcube(cb);
  fgets(buf, BUFMAX, stdin);
  doalg(cb, buf);
  printcube(cb);

  
  // char *ans = dfs(cb, dcross, 8);
  dfs(cb, dcross, 8);
  // if(ans)
  // {
  //   puts(ans);
  // }
  // else
  // {
  //   puts("could not find solution");
  // }

  
  // while(1)
  // {
  //   printcube(cb);
  //   // printf("cross: %d\n", dcross(cb));
  //   if(fgets(buf, BUFMAX, stdin) == 0) exit(0);
    
  //   doalg(cb, buf);
  // }
  
}
