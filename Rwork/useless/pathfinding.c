#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

int shortpath(int map[][28], int A, int B)
{
   int* M = (int*) calloc(868,sizeof(int));
   int find = 1;
   int i;
   int j;
   int n;
   int e;
   int s;
   int o;
   int trans = A;
   Cell *ctrans;
   ctrans = malloc(sizeof(*ctrans));
   ctrans->value = trans;
   *(M+A) = trans;
   TAILQ_HEAD(, Cell) file;
   TAILQ_INIT(&file);
   TAILQ_INSERT_HEAD(&file, ctrans, next);
   while (!TAILQ_EMPTY(&file) && find)
   {
      ctrans = TAILQ_FIRST(&file);
      trans = ctrans->value;
      TAILQ_REMOVE(&file, ctrans, next);
      free(ctrans);
      i = trans/28;
      j = trans%28;
      //north
      n = (i-1)*28 + j;
      Cell *N;
      N = malloc(sizeof(*N));
      N->value = n;
      //est
      e = i*28 + j + 1;
      Cell *E;
      E = malloc(sizeof(*E));
      E->value = e;
      //south
      s = (i+1)*28 + j;
      Cell *S;
      S = malloc(sizeof(*S));
      S->value = s;
      //west
      o = i*28 + j - 1;
      Cell *O;
      O = malloc(sizeof(*O));
      O->value = o;
      printf("%d,%d,%d,%d\n", n,e,s,o);
      if (map[i-1][j] != 0 && map[i-1][j] != 5 && *(M+n) == 0 && find)
      {     
         *(M+n) = trans;
	 if (n == B)
	    TAILQ_INSERT_HEAD(&file, N, next);
	 else
	    find = 0;
      }
      if (map[i][j+1] != 0 && map[i][j+1] != 5 && *(M+e) == 0 && find)
      {
         *(M+e) = trans;
	 if (e == B)
	    TAILQ_INSERT_HEAD(&file, E, next); 
	 else
	    find = 0;
      }
      if (map[i+1][j] != 0 && map[i+1][j] != 5 && *(M+s) == 0 && find)
      {
         *(M+s) = trans;
	 if (s == B)
	    TAILQ_INSERT_HEAD(&file, S, next);
	 else
	    find = 0;
      }
      if (map[i][j-1] != 0 && map[i][j-1] != 5 && *(M+o) == 0 && find)
      {
         *(M+o) = trans;
	 if (o == B)
	    TAILQ_INSERT_HEAD(&file, O, next);
	 else
	    find = 0;
      }
      printf("%d\n", 42);
   }
   printf("%d\n", B);   
   trans = B;
   while (*(M+trans) != A)
   { 
      trans = *(M+B);
   }
   return trans;
}  
