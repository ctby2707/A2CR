#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"
#include "ghost.h"
#include "pac-man.h"
int five_ray[20] =
{-140, -139, -109, -80, -23, 5, 33, 88, 115, 141, 140, 139, 109, 80, 23, -5, -33, -88, -115, -141};
int NE = 0;
int SE = 5;
int SW = 10;
int NW = 15;


// execute the pathfinding function for each ghost with parameters
void define_direction(Player *pl, char type, Game *game)
{
  int X_mat, Y_mat;
  pixel_To_MatCoord(pl->x, pl->y, &X_mat, &Y_mat);
  int X_pm, Y_pm;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_pm, &Y_pm);
  /*
     if(game.chase >0)
     {
     printf("invert coord \n");
     X_pm = 28-X_pm;
     Y_pm = 31-Y_pm;
     }
   */
  if (pl->dir == 'N')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat + 28);
    }
    else if (type == 'p')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat + 28);
    }
    else if (type == 'i')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat + 28);

      if (game->pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat + 28);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat + 28);
    }
  }
  else if (pl->dir == 'S')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat - 28);
    }
    else if (type == 'p')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat - 28);
    }
    else if (type == 'i')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat - 28);

      if (game->pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat - 28);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat - 28);
    }
  }
  else if (pl->dir == 'G')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat + 1);
    }
    else if (type == 'p')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'D')

        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat + 1);
    }
    else if (type == 'i')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat + 1);

      if (game->pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat + 1);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat + 1);
    }
  }
  else if (pl->dir == 'D')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat - 1);
    }
    else if (type == 'p')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat - 1);
    }
    else if (type == 'i')
    {
      if (game->pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
            game->map, X_mat * 28 + Y_mat - 1);

      if (game->pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
            game->map, X_mat * 28 + Y_mat - 1);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, game->map, X_mat * 28 + Y_mat - 1);
    }
  }
}

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

char blinky(int me, int pacman, int *map, int prev)
{
  int res = shortpath(map, prev, me, pacman);
  return NSGD(res);
}

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
  return NSGD(res);
}

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
  return NSGD(res);
}

char clyde(int me, int pacman, int *map, int prev)
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
  return NSGD(res);
}
