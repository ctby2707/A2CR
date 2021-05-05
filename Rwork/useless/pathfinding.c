<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "pathfinding.h"

int shortpath(int map[31][28], int A, int B)
{
   int* M = (int*) calloc(868,sizeof(int));
   int find = 1;
   int i;
   int j;
   int n;
   int e;
   int s;
   int o;
   int trans = A;
   *(M+A) = trans;
   int file;
   TAILQ_HEAD(tailhead, entry) head = TAILQ_HEAD_INITIALIZER(head);
   struct tailhead *headp;
   struct entry {
                TAILQ_ENTRY(entry) entries;
     } *n1, *n2, *n3, *np;
   TAILQ_INIT(&head);
   n1 = malloc(sizeof(struct entry));
   TAILQ_INSERT_HEAD(&head, n1, entries);
   while (!TAILQ_EMPTY(&head) && find)
   {
      trans = (int)TAILQ_FIRST(&head);
      TAILQ_REMOVE_HEAD(&head);
      i = trans/31;
      j = trans%31;
      n = (i-1)*31 + j;
      e = i*31 + j + 1;
      s = (i+1)*31 + j;
      o = i*31 + j - 1;
      if (map[i-1][j] != 0 && map[i-1][j] != 5 && *(M+n) == 0 && find)
      {
         *(M+n) = trans;
	 if (n == B)
	    TAILQ_INSERT_HEAD(&file, n, next);
	 else
	    find = 0;
      }
      if (map[i][j+1] != 0 && map[i][j+1] != 5 && *(M+e) == 0 && find)
      {
         *(M+e) = trans;
	 if (e == B)
	    TAILQ_INSERT_HEAD(&file, e, next); 
	 else
	    find = 0;
      }
      if (map[i+1][j] != 0 && map[i+1][j] != 5 && *(M+s) == 0 && find)
      {
         *(M+s) = trans;
	 if (s == B)
	    TAILQ_INSERT_HEAD(&file, s, next);
	 else
	    find = 0;
      }
      if (map[i][j-1] != 0 && map[i][j-1] != 5 && *(M+o) == 0 && find)
      {
         *(M+o) = trans;
	 if (o == B)
	    TAILQ_INSERT_HEAD(&file, e, next);
	 else
	    find = 0;
      }
   }
   trans = B;
   while (*(M+B) != A)
   { 
      trans = *(M+B);
   }
   return trans;
}  
=======
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

const int NORTH = -28;
const int SOUTH = 28;
const int EAST = 1;
const int WEST = -1;
int *M;

struct queue{
  struct queue *prev;
  struct queue *next;
  int elem;
  int head;//1=head    0=not the head
  int last;//1=last    0=not the last
  int unique; //  !0=unique     0=not unique
};

//remove the first element of the queue and return the new head of the queue.
struct queue *remove_first_elem(struct queue *q_head, int *elem)
{
  struct queue *useless = q_head;
  if ((q_head->last == 1) && q_head->unique != 1){
    q_head->elem =-1;
  }
  *elem = q_head->elem;
  q_head = useless->next;
  free(useless);
  return q_head;
}

//add an element to the queue and return the new last element.
struct queue *add_elem(struct queue *q_last, int elem, int *M, int prev)
{
  if(*(M+elem)==0)
  {
    struct queue  *new = malloc(sizeof(struct queue));
    new->prev=q_last;
    q_last->next = new;
    new->elem = elem;
    new->last = 1;
    q_last->last = 0;
    new->head=0;
    *(M+elem)=prev;
    return new;
  }
  else
    return q_last;
}

//give the coordonate of an element elem in the matrice map.
void coo(int elem, int *x, int *y)
{
  *y = elem%28;
  *x = elem/28;
}

// retrurn the new last element of the queue after have enqueue all the
//possible way from the current element.
struct queue *search_way(int map[][28],struct queue *q_last,int x,int y,int elem,int prev, int *M)
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
    q_last = add_elem(q_last,elem-28, M, prev);
  if (orientation[1]==1)
    q_last = add_elem(q_last,elem+28, M, prev);
  if (orientation[2]==1)
    q_last = add_elem(q_last,elem+1, M, prev);
  if (orientation[3]==1)
    q_last = add_elem(q_last,elem-1, M, prev);
  return q_last;
}

//return the direction that should be take by the ghost.
int shortpath(int map[][28], int prev, int A, int B)
{
  int find = 1;
  struct queue *q_head = malloc(sizeof(struct queue));
  q_head->head=1;
  M = calloc(868,sizeof(int));
  int x;
  int y;
  coo(A,&x,&y);
  struct queue *q_last;
  q_last = q_head;
  q_last->last = 1;
  q_last->unique = 1;
  q_head->elem =A;
  int elem = A;
  *(M+prev) = -1;
  q_last = search_way(map,q_last,x,y,A,A, M);
  while ((elem != -1) && find)
  {
    if (prev==A)
      *(M+prev) = -1;
    q_head = remove_first_elem(q_head, &elem);
    prev=elem;
    coo(elem, &x, &y);
    q_last = search_way(map, q_last, x, y, elem, prev, M);
  }
  int last = B;
  while (*(M+last)!=A)
    last=*(M+last);
  free(M);
  return last;
}
>>>>>>> 88bbe36b7a6df842c40986d6a861152cf0ce6488
