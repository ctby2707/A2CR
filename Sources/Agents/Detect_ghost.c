#include "queue.h"
#include <stddef.h>
#include <stdlib.h>

queue *enqueue_child_pac_gums(queue *q, int s, int *map, int *Vect_P, int *Vect_D, int dist);

int find_ghosts(int *map, int pos, char dir, int b, int i, int c, int p)
{
  int dist = 5;
  int res = 0;
  queue *q = NULL;
  int *Vect_P = calloc(868, sizeof(int));
  int *Vect_D = calloc(868, sizeof(int));
  q = queue_push(q, pos);
  Vect_D[pos] = 0;
  if(pos-28 > 0 && dir != 'N' && map[pos-28] != 0)
  {
    Vect_P[pos-28] = -1;
  }
  if(pos+28 < 868 && dir != 'S' && map[pos+28] != 0)
  {
    Vect_P[pos+28] = -1;
  }
  if(pos-1 > 0 && dir != 'W' && map[pos-1] != 0)
  {
    Vect_P[pos-1] = -1;
  }
  if(pos+1 < 868 && dir != 'E' && map[pos+1] != 0)
  {
    Vect_P[pos+1] = -1;
  }
  while (q != NULL)
  {
    int s;
    q = queue_pop(q, &s);
    if (s == b || s == i || s == p || s == c)
    {
      res = 1;
      break;
    }

    q = enqueue_child_pac_gums(q, s, map, Vect_P, Vect_D, dist);
  }
  free(Vect_P);
  free(Vect_D);
  queue_empty(&q);
  return res;;
}
queue *enqueue_child_pac_gums(queue *q, int s, int *map, int *Vect_P, int *Vect_D, int dist)
{
  if(Vect_D[s] != dist)
  {
    if ((s - 28 >= 0) && (Vect_P[s - 28] == 0) && map[s - 28] != 0) //N
    {
      Vect_P[s - 28] = s;
      Vect_D[s - 28] = Vect_D[s] + 1;
      q = queue_push(q, s - 28);
    }
    if ((s + 28 < 868) && (Vect_P[s + 28] == 0) && map[s + 28] != 0) //S
    {
      Vect_P[s + 28] = s;
      Vect_D[s + 28] = Vect_D[s] + 1;
      q = queue_push(q, s + 28);
    }
    if ((s - 1 >= 0) && (Vect_P[s - 1] == 0) && map[s - 1] != 0) //G
    {
      Vect_P[s - 1] = s;
      Vect_D[s - 1] = Vect_D[s] + 1;
      q = queue_push(q, s - 1);
    }
    if ((s + 1 < 868) && (Vect_P[s + 1] == 0) && map[s + 1] != 0) //D
    {
      Vect_P[s + 1] = s;
      Vect_D[s + 1] = Vect_D[s] + 1;
      q = queue_push(q, s + 1);
    }
  }
  return q;
}
