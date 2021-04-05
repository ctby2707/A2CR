#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"
#include "ghost.h"

int five_ray[20] =
    {-140, -139, -109, -80, -23, 5, 33, 88, 115, 141, 140, 139, 109, 80, 23, -5, -33, -88, -115, -141};
int NE = 0;
int SE = 5;
int SW = 10;
int NW = 15;

char NSGD(int res)
{
  if (res == -28)
    return 'N';
  if (res == 28)
    return 'S';
  if (res == -1)
    return 'G';
  if (res == 1)
    return 'D';
  return 'N';
}

char blinky(int me, int pacman, int map[][28], int prev)
{
  int res = shortpath((int *)map, prev, me, pacman);
  return NSGD(res);
}

char pinky(int me, int pacman, int dir_pacman, int map[][28], int prev)
{
  int dir_value;
  int B = pacman;
  dir_value = dir_pacman - pacman;
  if (dir_value != 0)
  {
    int Bp = B + dir_value;
    int mBp = map[Bp / 28][Bp % 28];
    while (mBp != 0 && mBp != 4 && mBp != 5)
    {
      B = Bp;
      Bp += dir_value;
      mBp = map[Bp / 28][Bp % 28];
    }
  }
  int res = shortpath((int *)map, prev, me, B);
  return NSGD(res);
}

char inky(int me, int blinky, int dir_pacman, int map[][28], int prev)
{
  int x1 = blinky / 28;
  int y1 = blinky % 28;
  int x2 = dir_pacman / 28;
  int y2 = dir_pacman % 28;
  int dx = x2 - x1;
  int dy = y2 - y1;
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
      a = dy / dx;
      b = y1 - x1 * a;
    }
    else
    {
      a = 0;
      b = y1;
    }
    int Bi = x2 + abs(dx) * dir_value;
    int Bj = Bi * a + b;
    B = Bi * 28 + Bj;
    int mBp = map[Bi][Bj];
    if (map[Bi][Bj] == 0 || map[Bi][Bj] >= 4)
    {
      while (mBp == 0 || mBp >= 4)
      {
        Bi += dir_value;
        Bj = a * Bi + b;
        B = Bi * 28 + Bj;
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
    int Bj = y2 + abs(dy) * dir_value;
    B = Bi * 28 + Bj;
    int mBp = map[Bi][Bj];
    if (mBp == 0 || mBp >= 4)
    {
      while (mBp == 0 || mBp >= 4)
      {
        Bj += dir_value;
        B = Bi * 28 + Bj;
        mBp = map[Bi][Bj];
      }
    }
  }
  int res = shortpath((int *)map, prev, me, B);
  return NSGD(res);
}

char clyde(int me, int pacman, int map[][28], int prev)
{
  int y1 = me % 28;     // horizontal coo of clyde
  int x1 = me / 28;     // vertical coo of clyde
  int y2 = pacman % 28; // horizontal coo of pacman
  //int x2 = pacman/28; // vertical coo of pacman
  int diagonal = 500; // the distance between target and clyde
  int final_target = 30;
  for (int i = 0; i < 20; i++)
  {
    int dir = five_ray[i];     //the coordonate we need to test compare to pacman
    int target = pacman + dir; // the current point we check
    if (target < 868 && target >= 0 && y2 + (dir % 28) < 28 && y2 + (dir % 28) >= 0 && map[target / 28][target % 28] > 0)
    { //check if the coordonnate can be use by clyde
      if ((abs((target % 28) - y1) + abs((target / 28) - x1)) < diagonal)
      {
        diagonal = abs((target % 28) - y1) + abs((target / 28) - x1);
        final_target = target;
      }
    }
  }
  //printf("final target = %d\n",final_target);
  int res = shortpath((int *)map, prev, me, final_target);
  return NSGD(res);
}
