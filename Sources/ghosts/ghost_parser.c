#include "game_init.h"
#include "blinky.h"
#include "inky.h"
#include "pinky.h"
#include "clyde.h"

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
