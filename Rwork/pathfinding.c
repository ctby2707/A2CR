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
   {5,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,5}, //10               
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

const int NORTH = 1;
const int SOUTH = 2;
const int EAST = 3;
const int WEST = 4;

typedef struct queue{
    struct queue *prev;
    struct queue *next;
    int elem;
}queue;

int remove_first_elem(queue *q)
{
  int elem = q->elem;
  if (q->next == NULL)
    return -1;
  q = q->next;
  q->prev = NULL;
  return elem;
}

void add_elem(queue *q, int elem)
{
  queue *save = q;
  while (save->next != NULL)
  {
    save = save->next;
  }
  queue *x;
  x->prev=save;
  x->next=NULL;
  x->elem = elem;
}

void coo(int elem, int *x, int *y)
{
  *y = elem/28;
  *x = elem%28;
}

queue *search_way(int map[][28],queue *q_last, int x, int y, int elem, int prev)
{
  int x_prev;
  int y_prev;
  coo(elem, &x_prev, &y_prev);
  int orientation[4]={1,1,1,1};
  if (map[x-1][y]==0 || x_prev+1==x)
  {
    orientation[0]=0;
    add_elem(q_last,elem-28);
  }
  if (map[x+1][y]==0 || x_prev-1==x)
  {
    orientation[1]=0;
    add_elem(q_last,elem+28);
  }
  if (map[x][y+1]==0 || y_prev-1==y)
  {
    orientation[2]=0;
    add_elem(q_last,elem+1);
  }
  if (map[x][y-1]==0 || y_prev+1==y)
  {
    orientation[3]=0;
    add_elem(q_last,elem-1);
  }


}

int shortpath(int map[][28], int prev, int A, int B)
{
  int* M = (int*) calloc(868,sizeof(int));
  int find = 1;
  queue *q_head;
  int x;
  int y;
  coo(q_head->elem,&x,&y);
  int orientation[4]={1,1,1,1};
  int x_prev;
  int y_prev;
  coo(prev, &x_prev, &y_prev);
  queue *q_last;
  q_last = q_head;
  int elem = A;
  int first = 0;
  q_last = search_way(map,q_last,x,y,A,prev);
  while ((elem != -1) && find)
  {
    prev=elem;
    elem = remove_first_elem(q_head);
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
    coo(elem, &x, &y);
    search_way(map, q_last, x, y, elem, prev);
  }
  return 0;
}
