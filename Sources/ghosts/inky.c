#include "pathfinding.h"
#include <stdlib.h>


char inky(int me, int blinky, int dir_pacman, int *map, int prev)
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
    int mBp = map[Bi*28+Bj];
    if (map[Bi*28+Bj] == 0 || map[Bi*28+Bj] >= 4)
    {
      while ((Bi <31) && (mBp == 0 || mBp >= 4))
      {
        Bi += dir_value;
        Bj = a * Bi + b;
        B = Bi * 28 + Bj;
        if(Bi < 0)
          break;
        mBp = map[Bi*28+Bj];
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
    int mBp = map[Bi*28+Bj];
    if (mBp == 0 || mBp >= 4)
    {
      while (mBp == 0 || mBp >= 4)
      {
        Bj += dir_value;
        B = Bi * 28 + Bj;
        mBp = map[Bi*28+Bj];
      }
    }
  }
  int res = shortpath((int *)map, prev, me, B);
  if (res == -28)
    return 'N';
  if (res == 28)
    return 'S';
  if (res == -1)
    return 'W';
  if (res == 1)
    return 'E';
  return 'N';
}
