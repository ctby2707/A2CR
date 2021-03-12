#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"
/*
   const int wall = 0;
   const int alley = 1;
   const int alley_pac_gum = 2;
   const int alley_super = 3;
   const int fantom_home = 4;
   const int tunnel = 5;
   const int map_ylen = 31;
   const int map_xlen = 28;



   int map[31][28] ={
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7                      
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0                
{0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0}, //1                
{0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //2                
{0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //3                
{0,2,2,2,2,3,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,3,2,2,2,2,0}, //4                
{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //5                
{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //6                
{0,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,0}, //7                
{0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //8                
{0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //9                
{5,2,2,2,2,2,2,1,1,1,&,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,5}, //10               
{0,2,0,0,0,0,2,0,0,1,0,0,0,4,4,0,0,0,1,0,0,2,0,0,0,0,2,0}, //11               
{0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //12               
{0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //13               
{0,2,2,2,2,2,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,2,2,2,2,2,0}, //14               
{0,1,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,0}, //15               
{0,1,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,1,0}, //16               
{0,1,1,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,1,1,0}, //17               
{0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,0,0,0}, //18               
{0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0}, //19               
{5,1,1,1,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,1,1,1,5}, //20               
{0,1,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,1,0}, //21               
{0,1,0,0,0,0,2,0,0,2,2,2,2,1,1,2,2,2,2,0,0,2,0,0,0,0,1,0}, //22               
{0,2,2,2,2,2,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,2,2,2,2,2,0}, //23               
{0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //24               
{0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //25               
{0,2,0,0,2,3,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,3,2,0,0,2,0}, //26               
{0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //27               
{0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //28               
{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0}, //29               
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //30  
 */

const int NORTH = -28;
const int SOUTH = 28;
const int EAST = 1;
const int WEST = -1;


typedef struct queue{
  struct queue *prev;
  struct queue *next;
  int elem;
  int head;//1=head    0=not the head
  int last;//1=last    0=not the last
}queue;

int remove_first_elem(queue *q)
{
  int elem = q->elem;
  if (q->last == 1)
    return -1;
  q = q->next;
  q->head=1;
  return elem;
}

void add_elem(queue *q_last, int elem)
{
  printf("q_last elem before change = %d\n",q_last->elem);
  queue  *new = malloc(sizeof(queue));
  new->prev=q_last;
  q_last->next = new;
  new->elem = elem;
  new->last = 1;
  q_last = new;
  printf("q_new elem = %d\n",new->elem);
  printf("q_last elem = %d\n",q_last->elem);
}

void coo(int elem, int *x, int *y)
{
  *y = elem/31;
  *x = elem%31;
}

void search_way(int map[][28],queue *q_last, int x, int y, int elem, int prev)
{
  int x_prev;
  int y_prev;
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

  if (orientation[0]==1)
    add_elem(q_last,elem-28);
  if (orientation[1]==1)
    add_elem(q_last,elem+28);
  if (orientation[2]==1)
    add_elem(q_last,elem+1);
  if (orientation[3]==1)
    add_elem(q_last,elem-1);
  printf("q_last elem in search_way=%d\n",q_last->elem);
  //printf("q_head elem in search_way=%d\n",q_head->elem);
}

int shortpath(int map[][28], int prev, int A, int B)
{
  int *M;
  printf("before calloc\n");
  M = calloc(868,sizeof(int));
  printf("calloc is not the problem\n");
  int find = 1;
  queue *q_head = malloc(sizeof(queue));
  q_head->head=1;
  int x;
  int y;
  coo(q_head->elem,&x,&y);
  int x_prev;
  int y_prev;
  coo(prev, &x_prev, &y_prev);
  queue *q_last;
  q_last = q_head;
  q_last->last = 1;
  q_last->elem =A;
  printf("elem just after%d\n",q_last->elem);
  int elem = A;
  int first = 0;
  int dir =0;
  search_way(map,q_last,x,y,A,prev);
  while ((elem != -1) && find)
  {
    printf("q_last elem =%d\n",q_last->elem);
    printf("q_head elem =%d\n",q_head->elem);
    prev=elem;
    elem = remove_first_elem(q_head);
    if (elem==B)
    {
      find=0;
      dir=*(M+prev);
      printf("%d\n",dir);
    }
    if (first==0)
    {
      first=-1;
      if (elem-1==A)
        *(M+elem)=WEST;
      if (elem+1==A)
        *(M+elem)=EAST;
      if (elem-28==A)
        *(M+elem)=SOUTH;
      if (elem+28==A)
        *(M+elem)=NORTH;
    }
    elsefile descripto
    {
      *(M+elem)=*(M+prev);
    }
    coo(elem, &x, &y);
    search_way(map, q_last, x, y, elem, prev);
    printf("q_last elem =%d\n",q_last->elem);
    printf("q_head elem =%d\n",q_head->elem);
  }
  free(M);
  return A+dir;
}
