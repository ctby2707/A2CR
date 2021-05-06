#include "queue.h"
#include <stddef.h>
#include <stdlib.h>
#include "pathfinding.h"

char find_close_pac_gum(int *map, int A, int *dir)
{
  int *Vect_P = calloc(868, sizeof(int));
  if(A-28 > 0 && dir[0] == 1 && map[A-28] != 0)
  {
    Vect_P[A-28] = -1;
  }
  if(A+28 < 868 && dir[1] == 1 && map[A+28] != 0)
  {
    Vect_P[A+28] = -1;
  }
  if(A-1 > 0 && dir[2] == 1 && map[A-1] != 0)
  {
    Vect_P[A-1] = -1;
  }
  if(A+1 < 868 && dir[3] == 1 && map[A+1] != 0)
  {
    Vect_P[A+1] = -1;
  }
  queue *q = NULL;
  q = queue_push(q, A);
  Vect_P[A] = -1;
  int s;
  while (q != NULL)
  {
    q = queue_pop(q, &s);
    if (map[s] == 2 || map[s] == 3)
    {
      break;
    }
    q = enqueue_child(q, s, map, Vect_P);
  }

  //find the direction
  int dire = s;
  while (Vect_P[dire] != A)
  {
    dire = Vect_P[dire];
    if(dire == 0)
      return 1;
  }
  free(Vect_P);
  queue_empty(&q);
  return dire - A;
}

