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
int *M;

struct queue{
  struct queue *prev;
  struct queue *next;
  int elem;
  int head;//1=head    0=not the head
  int last;//1=last    0=not the last
  int unique; //  !0=unique     0=not unique
};

struct queue *remove_first_elem(struct queue *q_head, int first_time, int *elem)
{
  //*elem = q_head->elem;
  //printf("remove elem = %d\n",*elem);
  struct queue *useless = q_head;
  //printf("remove q_head->last = %d\n",q_head->last);
  if ((q_head->last == 1) && q_head->unique != 1){
    q_head->elem =-1;
  }
  *elem = q_head->elem;
  q_head = useless->next;
 // q_head->head=1;
  free(useless);
  return q_head;
}

struct queue *add_elem(struct queue *q_last, int elem, int *M, int prev, int A)
{
  if(*(M+elem)==0)
  {
    //printf("q_last elem before change = %d\n",q_last->elem);
    struct queue  *new = malloc(sizeof(struct queue));
    new->prev=q_last;
    q_last->next = new;
    new->elem = elem;
    new->last = 1;
    q_last->last = 0;
    new->head=0;
    //q_last = new;
    //printf("q_new elem = %d\n",new->elem);
    //printf("q_last elem = %d\n\n",q_last->elem);
    printf("cocuocucoucocucoicucocucciucocucoicci %d\n",*(M+prev));
    printf("element = %d\n",elem);
    printf("previous = %d\n",prev);
    *(M+elem)=prev;
   /* if (elem == A)
      *(M+elem)=*(M+prev);
    else
    {
      if (elem+1==prev)
      {
        printf("WEST\n");
        *(M+elem)=WEST;
      }
      if (elem-1==prev){printf("EAST\n");
        *(M+elem)=EAST;}
      if (elem-28==prev){printf("SOUTH\n");
        *(M+elem)=SOUTH;}
      if (elem+28==prev){printf("NORTH\n");
        *(M+elem)=NORTH;}
    }*/
    //else
      //*(M+elem)=*(M+prev);
    return new;
  }
  else
    return q_last;
}

void coo(int elem, int *x, int *y)
{
  *y = elem%28;
  *x = elem/28;
}

struct queue *search_way(int map[][28],struct queue *q_last,int x,int y,int elem,int prev,
int *direction, int *M, int A)
{ // retrurn the unique direction or 0 if more than one direction
  //printf("putain de merde tu fonctionnes ou pas?\n");
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
  //int unique=0;
  int number=0;
  for(int i=0;i<4;i++)
  {
    if (orientation[i]==1)
    {
      number++;
      if(i==0)
        *direction=NORTH;
      if(i==1)
        *direction=SOUTH;
      if(i==2)
        *direction=EAST;
      if(i==3)
        *direction=WEST;
    }
  }
  if (number==1)
  {
    *direction = 0;
    return q_last;
  }

  if (orientation[0]==1)
    {//printf("HERE\n");
    q_last = add_elem(q_last,elem-28, M, prev, A);}
  if (orientation[1]==1){//printf("HERE\n");
    q_last = add_elem(q_last,elem+28, M, prev, A);}
  if (orientation[2]==1)
    q_last = add_elem(q_last,elem+1, M, prev, A);
  if (orientation[3]==1)
    q_last = add_elem(q_last,elem-1, M, prev, A);
  //printf("q_last elem in search_way=%d\n\n",q_last->elem);
  //printf("q_head elem in search_way=%d\n",q_head->elem);
  return q_last;
}

int number_elem(struct queue *q_head)
{
  int num = 0;
  for (struct queue *res = q_head;res->last!=1;res = res->next)
  {
    //printf("adress of the elem %d = %p\n",num+1,res);
    //printf("l'element c'est = %d\n",res->elem);
    num++;
  }
  //printf("\n\n\n\n\n\n");
  return num;
}

int shortpath(int map[][28], int prev, int A, int B)
{
  //printf("size of struct queue %ld\n",sizeof(struct queue));
  int find = 1;
  struct queue *q_head = malloc(sizeof(struct queue));
  q_head->head=1;
  M = calloc(868,sizeof(int));
  int x;
  int y;
  coo(A,&x,&y);
  //printf("x = %d et y = %d x_prev = %d et y_prev = %d\n",x,y,x_prev,y_prev);
  struct queue *q_last;// = malloc(sizeof(struct queue));
  q_last = q_head;
  q_last->last = 1;
  q_last->unique = 1;
  //printf("q_head->last = %d\n",q_head->last);
  //printf("q_last->last = %d\n",q_last->last);
  q_head->elem =A;
  //printf("q_head elem = %d  q_last->elem = %d\n",q_head->elem,q_last->elem);
  int elem = A;
  int first = 0;
  int final_dir = 0;
  int search=0;
  int direction;
  *(M+prev) = -1;
  q_last = search_way(map,q_last,x,y,A,A, &direction, M, A);
  while ((elem != -1) && find)
  {
    if (prev==A)
      *(M+prev) = -1;
    //printf("number total of element dans la queue = %d\n",number_elem(q_head));
    //printf("q_last elem =%d et l'adress est %p\n",q_last->elem,q_last);
    //printf("q_head elem =%d\n",q_head->elem);
    //printf("début de while avant remove q_head = %p\n",q_head);
    //prev=elem;
    if (first == 0)
    {
      first--;
      q_head = remove_first_elem(q_head, 0, &elem);
    }
    else
      q_head = remove_first_elem(q_head, 1, &elem);
    prev=elem;
    //printf("prev = %d\n",prev);
    //printf("après avoir remove pour comparaison q_head = %p\n",q_head);
    printf("THE ELEM= %d\n",elem);
    printf("PREV = %d\n",*(M+prev));
    if (elem!=A)
    {
      if (elem==B)
      {
        find=0;
        final_dir=*(M+prev);
        printf("previous last = %d\n",*(M+prev));
        printf("direction = %d\n",final_dir);
      }
      /*if (first==-1)
      {
        first=-1;
        printf("elem = %d, prev = %d \n",elem,prev);
        if (elem-1==prev)
        {
          printf("WEST\n");
          *(M+elem)=WEST;
        }
        if (elem+1==prev){printf("EAST\n");
          *(M+elem)=EAST;}
        if (elem-28==prev){printf("SOUTH\n");
          *(M+elem)=SOUTH;}
        if (elem+28==prev){printf("NORTH\n");
          *(M+elem)=NORTH;}
        printf("%d\n",*(M+elem));
      }*/
    }/*
    else
    {
      *(M+elem)=*(M+prev);
    }*/
    coo(elem, &x, &y);
    q_last = search_way(map, q_last, x, y, elem, prev, &direction,M, A);
    //printf("q_last elem =%d\n",q_last->elem);
    //printf("q_head elem =%d\n",q_head->elem);
  }
  int last = B;
  while (*(M+last)!=A)
  {
    printf("%d\n",*(M+last));
    last=*(M+last);
  }
  printf("coucou  = %d\n",last);
  free(M);
  return last;
}
