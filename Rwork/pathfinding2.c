#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include "pathfinding.h"
#include <err.h>

const int NORTH = -28;
const int SOUTH = 28;
const int EAST = 1;
const int WEST = -1;
int *M;// pas besoin de passer en paramètre M dans les fonction car il est
       // déclarer en externe

void print_matrix(int *M)
{
  int *k=M;
  for (int i =0;i<868;i++)
  {
    printf("%d,",*(M+i));
    if (*(M+i)%100!=*(M+i))
      printf(" ");
    else{
      if (*(M+i)==-1)
        printf("  ");
      else{
      if (*(M+i)%10!=*(M+i))
        printf("  ");
      else
        printf("   ");}}
    if ((i+1)%28==0 && i>0)
      printf("\n");
  }
  printf("\n\n\n");
}

//give the coordonate of an element elem in the matrice map.
void coo(int elem, int *x, int *y)
{
  *y = elem%28;
  *x = elem/28;
}

queue search_way(map[][28], int elem, int prev, queue q)
{
  int x;
  int y;
  int x_prev;
  int y_prev;
  coo(elem, &x, &y);
  coo(prev, &x_prev, &y_prev);
  int orientation[4]={1,1,1,1};


  if (map[x-1][y]==0 || x_prev+1==x)
    orientation[0]=0;
  if (map[x+1][y]==0 || x_prev-1==x)
    orientation[1]=0;
  if (map[x][y+1]==0 || y_prev-1==y)
    orientation[2]=0;
  if (map[x][y-1]==0 || y_prev+1==y)
    orientation[3]=0;

  int a=0;
  int save=0;
  for (int i =0;i<4;i++)
  {
    if (orientation[i] == 1)
    {
      a++;
      save=i;
    }
  }
  //prev=elem;
  if (a==1)
  {
    if (save==0)
      q.val = -28;
    if (save==1)
      q.val = 28;
    if (save==2)
      q.val = 1;
    if (save==3)
      q.val = -1;
    return q;
  }

  if (orientation[0]==1)
    q_last = add_elem(q_last,elem-28, M, prev);
  if (orientation[1]==1)
    q_last = add_elem(q_last,elem+28, M, prev);
  if (orientation[2]==1)
    q_last = add_elem(q_last,elem+1, M, prev);
  if (orientation[3]==1)
    q_last = add_elem(q_last,elem-1, M, prev);
  return q_last;


}

int shortpath(int map[][28], int prev, int A, int B)
{
  M = calloc(868,sizeof(int));
  queue q = NULL;
  *(M+prev) = -1;
  *(M+A) = -1;
  

  free(M);
}
