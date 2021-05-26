#include "pathfinding.h"

char pinky(int me, int pacman, int dir_pacman, int *map, int prev)
{
  int dir_value;
  int B = pacman;
  dir_value = dir_pacman - pacman;
  if (dir_value != 0)
  {
    int Bp = B + dir_value;
    int X = (Bp / 28);
    int Y = (Bp % 28);
    int mBp = 0;
    if(X >= 0 && X < 31 && Y >= 0 && Y < 28)
      mBp = map[X*28+Y];
    while (mBp != 0 && mBp != 4 && mBp != 5)
    {
      B = Bp;
      Bp += dir_value;
      X = (Bp / 28);
      Y = (Bp % 28);
      mBp = 0;
      if(X >= 0 && X < 31 && Y >= 0 && Y < 28)
        mBp = map[X*28+Y];
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
