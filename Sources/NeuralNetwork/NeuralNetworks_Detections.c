#include "NeuralNetworks_Detections.h"
#include <stddef.h>
#include <stdlib.h>

double find_pac_gum(int *map, int pos, int dir, int dist, int type)
{
  double pac_gum = 0;
  double nb_tile = -1;
  queue *q = NULL;
  int *Vect_P = calloc(868, sizeof(int));
  int *Vect_D = calloc(868, sizeof(int));
  q = queue_push(q, pos);
  Vect_D[pos] = 0;
  if(pos-28 > 0 && pos-28 != dir && map[pos-28] != 0)
  {
    Vect_P[pos-28] = -1;
  }
  if(pos+28 < 868 && pos+28 != dir && map[pos+28] != 0)
  {
    Vect_P[pos+28] = -1;
  }
  if(pos-1 > 0 && pos-1 != dir && map[pos-1] != 0)
  {
    Vect_P[pos-1] = -1;
  }
  if(pos+1 < 868 && pos+1 != dir && map[pos+1] != 0)
  {
    Vect_P[pos+1] = -1;
  }
  while (q != NULL)
  {
    int s;
    q = queue_pop(q, &s);
    nb_tile++;
    if (map[s] == type)
    {
      pac_gum++;
    }
    q = enqueue_child_pac_gum(q, s, map, Vect_P, Vect_D, dist);
  }
  free(Vect_P);
  free(Vect_D);
  queue_empty(&q);

  return pac_gum / nb_tile;
}

double find_ghost(int *map, int pos, int dir, int dist, int b, int i, int c, int p)
{
 double nb_ghost = 0;
  queue *q = NULL;
  int *Vect_P = calloc(868, sizeof(int));
  int *Vect_D = calloc(868, sizeof(int));
  q = queue_push(q, pos);
  Vect_D[pos] = 0;
  if(pos-28 > 0 && pos-28 != dir && map[pos-28] != 0)
  {
    Vect_P[pos-28] = -1;
  }
  if(pos+28 < 868 && pos+28 != dir && map[pos+28] != 0)
  {
    Vect_P[pos+28] = -1;
  }
  if(pos-1 > 0 && pos-1 != dir && map[pos-1] != 0)
  {
    Vect_P[pos-1] = -1;
  }
  if(pos+1 < 868 && pos+1 != dir && map[pos+1] != 0)
  {
    Vect_P[pos+1] = -1;
  }
  while (q != NULL)
  {
    int s;
    q = queue_pop(q, &s);
    if (s == b)
      nb_ghost++;
    if(s == i)
      nb_ghost++;
    if(s == c)
      nb_ghost++;
    if(s == p)
      nb_ghost++;

    q = enqueue_child_pac_gum(q, s, map, Vect_P, Vect_D, dist);
  }
  free(Vect_P);
  free(Vect_D);
  queue_empty(&q);
  return nb_ghost/4;
}
queue *enqueue_child_pac_gum(queue *q, int s, int *map, int *Vect_P, int *Vect_D, int dist)
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
