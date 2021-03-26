#ifndef PATHFINDING_H
#define PATHFINDING_G
#include <sys/queue.h>

typedef struct Cell
{
   int value;
   TAILQ_ENTRY(Cell) next;
} Cell;

int shortpath(int map[][28], int A, int B);

#endif
