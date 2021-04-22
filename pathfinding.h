#ifndef PATHFINDING_H
#define PATHFINDING_G
#include "queue.h"

int shortpath(int *map, int prev, int A, int B);
queue *enqueue_child(queue *q, int s, int *map, int *Vect_P);

#endif
