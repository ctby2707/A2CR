#include "pathfinding.h"

char blinky(int me, int pacman, int *map, int prev)
{
  int res = shortpath(map, prev, me, pacman);
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
