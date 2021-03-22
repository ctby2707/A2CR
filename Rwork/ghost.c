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

int pinky (int me, int dir_pacman, int map[][28])
{
  //TODO
}

int inky (int me, int blinky, int pacman, int map[][28])
{
  //TODO
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
}

int clyde (int me, int pacman, int map[][28])
{
  int y1 = me%28;
  int x1 = me/28;
  int y2 = pacman%28;
  int x2 = pacman/28;
  int direction = GPS(x1,y1,x2,y2);
  int node=56;
  int top;
  int stock;
  int the_good_one;
  for (int i=direction;i<direction+5;i++)
  {
    if (pacman+five_ray[direction]<868 && pacman+five_ray[direction]>=0)
    {
      top = pacman + five_ray[i];
      if ((stock = abs((top%28)-y1) + abs((top/28)-x1))<node)
      {
        the_good_one = i;
        node = stock;
      }
    }
  }
  return the_good_one;
}
