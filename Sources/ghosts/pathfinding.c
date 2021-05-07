#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <err.h>
#include "queue.h"
#include "pathfinding.h"

int shortpath(int *map, int prev, int A, int B)
{
  //Check conformity of parameters
  /*if(A < 0 || A > 868)
    printf("Ghost position is not conform: A = %i\n",A);
  if(B < 0 || B > 868)
    printf("Target position is not conform : B = %i\n",B);
  if(map[A] == 0)
    printf("Ghost position is wall (A = 0)\n");
  if(map[B] == 0)
    printf("Target position is a wall (B = 0) cheh\n");
  if(A == B)
    printf("A and B are the same\n");*/

  if (A == B || B < 0 || B > 868 || A < 0 || A > 868 || map[B] == 0 || map[A] == 0)
  {//error management
    if (map[A - 28] != 0)
      return -28;
    if (map[A + 28] != 0)
      return 28;
    if (map[A - 1] != 0)
      return -1;
    return 1;
  }
  if (B == prev)
    return A - prev;

  queue *q = NULL;
  int *Vect_P = calloc(868, sizeof(int));
  q = queue_push(q, A);
  Vect_P[A] = -1;
  Vect_P[prev] = -1;
  while (q != NULL)
  {
    int s;
    q = queue_pop(q, &s);
    if (s == B) //B found
    {
      break;
    }
    q = enqueue_child(q, s, map, Vect_P);
  }

  //find the direction
  int dir = B;
  while (Vect_P[dir] != A)
    dir = Vect_P[dir];
  free(Vect_P);
  queue_empty(&q);
  return dir - A;
}

queue *enqueue_child(queue *q, int s, int *map, int *Vect_P)
{
  if ((s - 28 >= 0) && (Vect_P[s - 28] == 0) && map[s - 28] != 0) //N
  {
    Vect_P[s - 28] = s;
    q = queue_push(q, s - 28);
  }
  if ((s + 28 < 868) && (Vect_P[s + 28] == 0) && map[s + 28] != 0) //S
  {
    Vect_P[s + 28] = s;
    q = queue_push(q, s + 28);
  }
  if ((s - 1 >= 0) && (Vect_P[s - 1] == 0) && map[s - 1] != 0) //G
  {
    Vect_P[s - 1] = s;
    q = queue_push(q, s - 1);
  }
  if ((s + 1 < 868) && (Vect_P[s + 1] == 0) && map[s + 1] != 0) //D
  {
    Vect_P[s + 1] = s;
    q = queue_push(q, s + 1);
  }

  //teleporters
  if(map[s] == 42 && Vect_P[307] == 0)
  {
    Vect_P[307] = s;
    q = queue_push(q, 307);
  }
  if(map[s] == 43 && Vect_P[280] == 0)
  {
    Vect_P[280] = s;
    q = queue_push(q, 280);
  }
  if(map[s] == 44 && Vect_P[587] == 0)
  {
    Vect_P[587] = s;
    q = queue_push(q, 587);
  }
  if(map[s] == 45 && Vect_P[560] == 0)
  {
    Vect_P[560] = s;
    q = queue_push(q, 560);
  }

  return q;
}
