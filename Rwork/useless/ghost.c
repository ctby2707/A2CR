#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"
#include "ghost.h"

int five_ray[20] =
{-140,-139,-109,-80,-23,5,33,88,115,141,140,139,109,80,23,-5,-33,-88,-115,-141};
int NE = 0;
int SE = 5;
int SW = 10;
int NW = 15;

int blinky (int me, int pacman, int map[][28])
{
  return shortpath(map, me, me, pacman);
}

int pinky (int me, int pacman, int dir_pacman, int map[][28])
{
  int dir_value;
  int B = pacman;
  if (dir_pacman > pacman)
       dir_value = dir_pacman - pacman;
  else
       dir_value = pacman - dir_pacman;
  if (dir_value != 0)
  {
       int Bp = B + dir_value;
       int mBp = map[Bp/28][Bp%28];
       while (mBp != 0 && mBp != 4 && mBp != 5)
       {	   
           B = Bp;
	   Bp += dir_value;
	   mBp = map[Bp/28][Bp%28];
       }
  }
  return shortpath(map, me, me, B);
}

int inky (int me, int blinky, int dir_pacman, int map[][28], int prev)
{
  int x1 = blinky/28;
  int y1 = blinky%28;
  int x2 = dir_pacman/28;
  int y2 = dir_pacman%28;
  int dx = x2-x1;
  int dy = y2-y1;
  int a;
  int b;
  int dir_value;
  int B = dir_pacman;
  if (dx != 0)
  {
       if (dx > 0)
	   dir_value = 1;
       else
	   dir_value = -1;
       if (dy != 0)
       {
	   a = dy/dx;
	   b = y1 - x1*a;
       }
       else
       {
	   a = 0;
	   b = y1;
       }
       int Bi = x2 + abs(dx)*dir_value;
       int Bj = Bi*a + b;
       B = Bi*28 + Bj;
       int mBp = map[Bi][Bj];
       if (map[Bi][Bj] == 0 || map[Bi][Bj] >= 4)
       {
       	while (mBp == 0 || mBp >= 4)
       	{
	   	Bi += dir_value;
	   	Bj = a*Bi + b;
	  	B = Bi*28 + Bj;
	   	mBp = map[Bi][Bj];
       	}
       }
  }
  else
  {
       if (dy > 0)
	   dir_value = 1;
       else
	   dir_value = -1;
       int Bi = x2;
       int Bj = y2 + abs(dy)*dir_value;
       B = Bi*28 + Bj;
       int mBp = map[Bi][Bj];
       if (mBp == 0 || mBp >= 4)
       {
       	while (mBp == 0 || mBp >= 4)
       	{
	   Bj += dir_value;
	   B = Bi*28 + Bj;
	   mBp = map[Bi][Bj];
       	}
       }
   }
   return shortpath(map, prev, me, B);
}

int GPS(int x1, int y1, int x2, int y2)
{
  if (x2<x1 && y2<=y1)
    return SE;
  if (x2>x1 && y2>=y1)
    return NW;
  if (x2<=x1 && y2>y1)
    return SW;
  if (x2>=x1 && y2<y1)
    return NE;
  return 0;
}

int clyde (int me, int pacman, int map[][28])
{
  int y1 = me%28;
  int x1 = me/28;
  int y2 = pacman%28;
  int x2 = pacman/28;
  int direction = GPS(x1,y1,x2,y2);
  printf("the direction is = %d\n",direction);
  int node=500;
  int top;
  int stock;
  int the_good_one;
  for (int i=direction;i<direction+5;i++)
  {
    int dir = five_ray[i];
    int target = pacman + dir;
    printf("target = %d && y2+dir = %d && map =%d\n",target,y2+dir,map[target/28][target%28]);
    if (target<868 && target>=0 && y2+(dir%28)<28 && y2+(dir%28)>=0 &&
map[target/28][target%28]>0 && map[target/28][target%28]!=4)
    {
      top = pacman + five_ray[i];
      printf("%d\n",abs((top%28)-y1) + abs((top/28)-x1));
      if ((stock = abs((top%28)-y1) + abs((top/28)-x1))<node)
      {
        the_good_one = dir+pacman;
        printf("the good one is %d && %d\n",the_good_one,abs((top%28)-y1) + abs((top/28)-x1));
        node = stock;
      }
    }
  }
  return the_good_one;
}
