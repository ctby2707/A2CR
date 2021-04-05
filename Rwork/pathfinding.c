#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "pathfinding.h"
#include <err.h>

const int NORTH = -28;
const int SOUTH = 28;
const int EAST = 1;
const int WEST = -1;
int *M;// pas besoin de passer en paramètre M dans les fonction car il est
       // déclarer en externe

struct queue{
  struct queue *prev;
  struct queue *next;
  int elem;
  int head;//1=head    0=not the head
  int last;//1=last    0=not the last
  int unique; //  !0=unique     0=not unique
};

void print_matrix(int *M)
{
  //int *k=M;
  for (int i =0;i<868;i++)
  {
    printf("%d,",*(M+i));
    if (*(M+i)%100!=*(M+i))
      printf(" ");
    else{
      if (*(M+i)<0)
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
//remove the first element of the queue and return the new head of the queue.
struct queue *remove_first_elem(struct queue *q_head, int *elem)
{
  printf("q_head = %p\n",(void *)q_head);
  printf("q_head->elem = %d\n",q_head->elem);
  struct queue *useless = q_head;
  /*if ((q_head->last == 1)){ //&& q_head->unique != 1){
    q_head->elem =-1;
  }*/
  *elem = q_head->elem;
  q_head = useless->next;
  free(useless);
  return q_head;
}

//add an element to the queue and return the new last element.
struct queue *add_elem(struct queue *q_last, int elem, int *M, int prev)
{
  printf("elem in add = %d\n",elem);
  print_matrix(M);
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
struct queue *search_way(int map[][28],struct queue *q_last,int x,int y,int
elem,int prev, int *M, int A)
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
  if (elem==A)
  {
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
    if (a==1)
    {
      if (save==0)
        q_last->elem=-28;
      if (save==1)
        q_last->elem=28;
      if (save==2)
        q_last->elem=1;
      if (save==3)
        q_last->elem=-1;
      return q_last;
    }
  prev=elem;
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


//return the direction that should be take by the ghost.
int shortpath(int map[][28], int prev, int A, int B)
{
  if (A==B)
    err(3,"same case");
  int find = 1;
  struct queue *q_head = malloc(sizeof(struct queue));
  q_head->head=1;
  M = calloc(868,sizeof(int));
  //printf("M = %p\n",(void*)M);
  int x;
  int y;
  coo(A,&x,&y);
  struct queue *q_last;
  q_last = q_head;
  q_last->last = 1;
  q_last->unique = 1;
  q_head->elem =A;
  int elem = A;
  *(M+prev) = -2;
  printf("avant prev = %d && elem = %d\n",prev,elem);
  q_last = search_way(map,q_last,x,y,A,prev, M,A);

  if (q_last->elem==-1 || q_last->elem==1 || q_last->elem==28 || q_last->elem==-28)
  {
    struct queue *freed;
    while (q_head->last!=1)
    {
      freed=q_head;
      q_head=q_head->next;
      free(freed);
    }
    free(q_head);
    free(M);
    return q_last->elem;
  }
  prev=elem;
  q_head = remove_first_elem(q_head, &elem);
  while (find)//(elem != -1) && find)
  {
    int trans;
    //printf("elem = %d\n",elem);
    //printf("prev = %d\n",prev);
    if (prev==A)
      *(M+prev) = -1;
    trans = elem;
    //print_matrix(M);
    q_head = remove_first_elem(q_head, &elem);
    printf("return of remove elem = %d && prev = %d\n",elem,prev);
    coo(elem, &x, &y);
    q_last = search_way(map, q_last, x, y, elem, prev, M, A);
    prev=trans;
    if (elem==B)
      find=0;
  }
  //printf("elem = %d\n",elem);
  //printf("prev = %d\n",prev);
  int last = B;
  while (*(M+last)!=A)
  {
    //printf("last = %d et A = %d\n",last,A);
    last=*(M+last);
    //print_matrix(M);
    if (last==0)
    {
      printf("last should be 0 here last = %d et A = %d\n",last,A);
      err(3,"error last should not be 0");}
  }
  //printf("M at the end = %p\n",(void *)M);
  struct queue *freed;
  while (q_head->last!=1)
  {
    freed=q_head;
    q_head=q_head->next;
    free(freed);
  }
  free(q_head);
  free(M);
  //printf("q_head = %p\n",(void *)q_head);
  return last-A;
}
