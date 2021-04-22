#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <math.h>
#include <err.h>
/*
   typedef struct node = {
   int cost;
   float heur;
   int dir;
   int elem;
   int prev;

   }node;*/

void print_matrix(node *M) //!!!debbuging function!!!
{
  //int *k=M;
  for (int i = 0; i < 868; i++)
  {
    printf("%d,", M[i].elem);
    if (M[i].elem % 100 != M[i].elem)
      printf(" ");
    else
    {
      if (M[i].elem < 0)
        printf("  ");
      else
      {
        if (M[i].elem % 10 != M[i].elem)
          printf("  ");
        else
          printf("   ");
      }
    }
    if ((i + 1) % 28 == 0 && i > 0)
      printf("\n");
  }
  printf("\n\n\n");
}

//regarder par rapport au noeud ou on se trouve si il y a un noeud dans la liste
//ouverte qui a un cout moindre ça voudrait dire qu'il faut y aller
float heuristic(int cost_prev, int elem, int B)
{
  return cost_prev + sqrt((pow(abs((B % 28) - (elem % 28)),2)) + (pow(abs((B / 28) - (elem / 28)),2)));
}

//return 1 if the element is in the list and the one on the openlist have an
//inferior heuristic cost otherwise it return 0;
/*int is_in_q(queue *q, node target)//target is the elem we want to know if it is on the list
  {
  while (q != NULL)
  {
  if (q->val.elem == target.elem && q->val.heur >= target.heur)
  return 1;
  q = q->next;
  }
  return 0;
  }*/
int is_in_q(queue *q, node target)
{
  queue *start = q;
  q = q->next;
  do
  {
    if (q->val.elem == target.elem && q->val.heur >= target.heur)
      return 1;
    q = q->next;
  }while(q != start);
  if (q->val.elem == target.elem && q->val.heur >= target.heur)
    return 1;
  return 0;
}
//change the enqueue_children to the good way of A*.
//enqueue all the possible neighboor
queue *enqueue_children(queue *q, int s, int *map)
{
  if ((s - 28 > 0) && *(map +s-28) != 0) //N
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

int shortpath(int *map, int prev, int A, int B)
{
  printf("Précédent = %d et Départ = %d et Arrivé = %d\n",prev,A,B);
  node *Vect_P = calloc(868, sizeof(node));
  queue *open = NULL;
  node first;
  first.heur = 0;
  //first.dir;
  first.cost = 0;
  first.elem = A;
  first.prev= prev;
  open = queue_push(open, first);
  //queue_print(&open);
  int i=0;//debug
    queue_print(open);
  while (open != NULL)
  {
    node d;
    open = queue_pop(open, &d);
    printf("2 : elem dequeue = %d\n",d.elem);
    if (d.elem == B)
      return d.dir;
    printf("here");
    queue *nigh = NULL;
    nigh = (queue *) enqueue_children(nigh, d.elem, map);
    printf("print of the neighbour list :\n");
    queue_print(nigh);
    printf("prev = %d\n",prev);
    printf("\n");
      int j =0;//debug
    while (nigh != NULL)
    {
      node neighbour;
      nigh = queue_pop(nigh, &neighbour);
      if (!((Vect_P+ d.elem)->elem != 0 && is_in_q(open, d) == 0) && neighbour.elem != d.elem)
      {
        j++;
        neighbour.cost = d.cost + 1;
        neighbour.heur = neighbour.cost + heuristic(d.cost, neighbour.elem, B);
        if (d.elem == A)
          neighbour.dir = neighbour.elem - d.elem;
        else
          neighbour.dir = d.dir;
        neighbour.prev=d.elem;
        open = queue_push(open, neighbour);
      }
    }
      printf("number of neighbour add : %d\n",j);
    prev = d.elem;
    *(Vect_P + d.elem) = d;
    printf("print of the open list :\n");
    queue_print(open);
    printf("\n\n\n");
    if (i==6)
      err(3,"too many\n");
    i++;
  }
  printf("error return\n");
  queue_empty(&open);
  return 0;
}
