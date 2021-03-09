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
   Cell *neso;
   ctrans->value = trans;
   *(M+A) = trans;
   SLIST_HEAD(, Cell) file;
   SLIST_INIT(&file);
   SLIST_INSERT_HEAD(&file, ctrans, next);
   while (!SLIST_EMPTY(&file) && find)
   {
      ctrans = SLIST_FIRST(&file);
      trans = ctrans->value;
      SLIST_REMOVE_HEAD(&file,);
      i = trans/31;
      j = trans%31;
      n = (i-1)*31 + j;
      e = i*31 + j + 1;
      s = (i+1)*31 + j;
      o = i*31 + j - 1;
      if (map[i-1][j] != 0 && map[i-1][j] != 5 && *(M+n) == 0 && find)
      {
         *(M+n) = trans;
	 neso->value = n;
	 if (n == B)
	    SLIST_INSERT_HEAD(&file, neso, next);
	 else
	    find = 0;
      }
      if (map[i][j+1] != 0 && map[i][j+1] != 5 && *(M+e) == 0 && find)
      {
         *(M+e) = trans;
	 neso->value = e;
	 if (e == B)
	    SLIST_INSERT_HEAD(&file, neso, next); 
	 else
	    find = 0;
      }
      if (map[i+1][j] != 0 && map[i+1][j] != 5 && *(M+s) == 0 && find)
      {
         *(M+s) = trans;
	 neso->value = s;
	 if (s == B)
	    SLIST_INSERT_HEAD(&file, neso, next);
	 else
	    find = 0;
      }
      if (map[i][j-1] != 0 && map[i][j-1] != 5 && *(M+o) == 0 && find)
      {
         *(M+o) = trans;
	 neso->value = o;
	 if (o == B)
	    SLIST_INSERT_HEAD(&file, neso, next);
	 else
	    find = 0;
      }
   }
   trans = B;
   while (*(M+B) != A)
   { 
      trans = *(M+B);
   }
   return trans;
}  
