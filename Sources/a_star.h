#ifndef A_STAR_H                                                                  
#define A_STAR_H

typedef struct node {
  int cost;
  float heur;
  int dir;
  int elem;

}node;

int shortpath(int map, int prev, int A, int B);

#endif
