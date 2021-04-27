#ifndef NEURALNETWORKS_DETECTION_H
#define NEURALNETWORKS_DETECTION_H

#include "queue.h"

double find_pac_gum(int *map, int pos, int dir, int dist, int type);
double find_ghost(int *map, int pos, int dir, int dist, int b, int i, int c, int p);
queue *enqueue_child_pac_gum(queue *q, int s, int *map, int *Vect_P, int *Vect_D, int dist);

#endif
