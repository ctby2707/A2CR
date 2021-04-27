#include "pathfinding.h"

char pinky(int me, int pacman, int dir_pacman, int *map, int prev)
{
  int dir_value;
  int B = pacman;
  dir_value = dir_pacman - pacman;
  if (dir_value != 0)
  {
    int Bp = B + dir_value;
    int mBp = map[(Bp / 28)*28+(Bp % 28)];
    while (mBp != 0 && mBp != 4 && mBp != 5)
    {
      B = Bp;
      Bp += dir_value;
      mBp = map[(Bp / 28)*28+(Bp % 28)];
    }
  }
  int res = shortpath((int *)map, prev, me, B);
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
