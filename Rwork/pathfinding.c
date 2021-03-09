#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"
#include "fifo.h"

int shortpath(int map[], int A, int B)
{
   int* M = (int*) calloc(868,sizeof(int));
   int find = 1;
   int start = A;
   int end = B;
   int neigh;
   int trans = start;
   *(M+A) = trans;
   File F = Emptyfile();
   Puton (F,A);
   while (Length(F) && find)
   {
      trans = Scrolling(F);
      neigh = trans;
      neigh++;
      if (map[neigh] != 0 && *(M+neigh) == 0 && find)
      {
         *(M+neigh) = trans;
	 if (neigh != end)
            Puton (F,neigh);
	 else
	    find = 0;
      }
      neigh -= 2;
      if (map[neigh] != 0 && *(M+neigh) == 0 && find)
      {
         *(M+neigh) = trans;
	 if (neigh != end)
            Puton (F,neigh);
	 else
	    find = 0;
      }
      neigh += 32;
      if (map[neigh] != 0 && *(M+neigh) == 0 && find)
      {
         *(M+neigh) = trans;
	 if (neigh != end)
            Puton (F,neigh);
	 else
	    find = 0;
      }
      neigh -= 62;
      if (map[neigh] != 0 && *(M+neigh) == 0 && find)
      {
         *(M+neigh) = trans;
	 if (neigh != end)
            Puton (F,neigh);
	 else
	    find = 0;
      }
   }
   int next = end;
   while (*M+next != start)
   { 
      next = *M+next;
   }
   return next;
}  
