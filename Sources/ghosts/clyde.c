#include <stdlib.h>
#include "pathfinding.h"

char clyde(int me, int pacman, int *map, int prev)
{
  int five_ray[20] = {-140, -139, -109, -80, -23, 5, 33, 88, 115, 141, 140,
                      139, 109, 80, 23, -5, -33, -88, -115, -141};
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
    if (target < 868 && target >= 0 && y2 + (dir % 28) < 28 && y2 + (dir % 28) >= 0 && map[(target / 28)*28+(target % 28)] > 0)
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
