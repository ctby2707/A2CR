#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "pathfinding.h"

int shortpath(int map[31][28], int A, int B)
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
   *(M+A) = trans;
   int file;
   TAILQ_HEAD(tailhead, entry) head = TAILQ_HEAD_INITIALIZER(head);
   struct tailhead *headp;
   struct entry {
                TAILQ_ENTRY(entry) entries;
     } *n1, *n2, *n3, *np;
   TAILQ_INIT(&head);
   n1 = malloc(sizeof(struct entry));
   TAILQ_INSERT_HEAD(&head, n1, entries);
   while (!TAILQ_EMPTY(&head) && find)
   {
      trans = (int)TAILQ_FIRST(&head);
      TAILQ_REMOVE_HEAD(&head);
      i = trans/31;
      j = trans%31;
      n = (i-1)*31 + j;
      e = i*31 + j + 1;
      s = (i+1)*31 + j;
      o = i*31 + j - 1;
      if (map[i-1][j] != 0 && map[i-1][j] != 5 && *(M+n) == 0 && find)
      {
         *(M+n) = trans;
	 if (n == B)
	    TAILQ_INSERT_HEAD(&file, n, next);
	 else
	    find = 0;
      }
      if (map[i][j+1] != 0 && map[i][j+1] != 5 && *(M+e) == 0 && find)
      {
         *(M+e) = trans;
	 if (e == B)
	    TAILQ_INSERT_HEAD(&file, e, next); 
	 else
	    find = 0;
      }
      if (map[i+1][j] != 0 && map[i+1][j] != 5 && *(M+s) == 0 && find)
      {
         *(M+s) = trans;
	 if (s == B)
	    TAILQ_INSERT_HEAD(&file, s, next);
	 else
	    find = 0;
      }
      if (map[i][j-1] != 0 && map[i][j-1] != 5 && *(M+o) == 0 && find)
      {
         *(M+o) = trans;
	 if (o == B)
	    TAILQ_INSERT_HEAD(&file, e, next);
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
