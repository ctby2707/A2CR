#include <stdio.h>
#include <queue.h>
#include <math.h>
/*
typedef struct node = {
  int cost;
  float heur;
  int dir;
  int elem;

}node;*/


//regarder par rapport au noeud ou on se trouve si il y a un noeud dans la liste
//ouverte qui a un cout moindre ça voudrait dire qu'il faut y aller
float heuristic(int cost_prev, int elem, int B)
{
  return cost_prev + sqrt(((abs((B % 28) - (elem % 28)))**2 + (abs((B / 28) -
            (elem / 28))))**2);
}

//I don't know how to calculate the heuristic cost for the moment
int shortpath(int map, int prev, int A, int B)
{
  node Vect_P = calloc(868, sizeof(node));
  queue *open = NULL;
  node first;
  first.heur = 0;
  first.dir;
  first.cost = 0;
  first.elem = A;
  open = queue_push(open, first);
  while (open != NULL)
  {
    node d;
    open = queue_pop(open, &d);
    if (d == B)
      return d.dir;
    queue *nigh = NULL;
    nigh = enqueue_children(nigh, d.elem, map);
    while (nigh != NULL)
    {
      node neighbour;
      nigh = queue_pop(nigh, neighbour);
      if (!(Vect_P[d.elem].elem != 0 && is_in_q(open, d) == 0))
      {
        neighbour.cost = d.cost + 1;
        neighbour.heur = neighbour.cost + heuristic(d.cost, neighbour, B);
        if (d.elem == A)
          neighbour.dir = neighbour.elem - d.elem;
        else
          neighbour.dir = d.dir;
        queue_push(open, neighbour);
      }
    }
    Vect_P[d.elem]=d;
  }
  return 0;
}

//return 1 if the element is in the list and the one on the openlist have an
//inferior heuristic cost otherwise it return 0;
int is_in_q(queue *q, node target)//target is the elem we want to know if it is on the list
{
  while (q != NULL)
  {
    if (q->val.elem == target.elem && q->val.heur >= target.heur)
      return 1;
    q->next = q->next->next;
  }
  return 0;
}
//change the enqueue_children to the good way of A*.
//enqueue all the possible neighboor
queue *enqueue_children(queue *q, int s, int map)
{
  if ((s - 28 > 0) && map[s - 28] != 0) //N
  {
    node N;
    N.elem = s-28;
    q = queue_push(q, N);
  }
  if ((s + 28 < 868) && map[s + 28] != 0) //S
  {
    node S;
    S.elem = s+28;
    q = queue_push(q, S);
  }
  if ((s - 1 >= 0) && map[s - 1] != 0) //G
  {
    node G;
    G.elem = s-1;
    q = queue_push(q, G);
  }
  if ((s + 1 < 868) && map[s + 1] != 0) //D
  {
    node D;
    D.elem = s+1;
    q = queue_push(q, D);
  }
  return q;
}

