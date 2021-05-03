#include "game_init.h"
#include "blinky.h"

void define_scater_mode(Game *game, Player *pl)
{

  int XB, YB;
  pixel_To_MatCoord(pl->x, pl->y, &XB, &YB);
  //printf("dir = %c \n",pl->dir);


  if(pl->list[pl->n] == XB*28 + YB)
  {
    //printf("changed from %i\n",pl->list[pl->n]);
    //change the coord destination to the next point in the list
    pl->n= pl->n + 1;
    //printf("going to %i\n",pl->list[pl->n]);
  }

  if(game->blinky.n > 3)
  {
    game->blinky.n = 0;
  }
  if(game->clyde.n > 4)
  {
    game->clyde.n = 0;
  }
  if(game->inky.n > 4)
  {
    game->inky.n = 0;
  }
  if(game->pinky.n > 3)
  {
    game->pinky.n = 0;
  }



  if(pl->dir == 'N')
  {

    pl->dir = blinky(XB * 28 + YB, pl->list[pl->n],game->map, XB * 28 + YB +28);

  }
  else
  {
    if(pl->dir == 'S')
    {

      pl->dir = blinky(XB * 28 + YB, pl->list[pl->n],game->map, XB * 28 + YB - 28);

    }
    else
    {
      if(pl->dir =='G')
      {

        pl->dir = blinky(XB * 28 + YB, pl->list[pl->n],game->map, XB * 28 + YB +1);

      }
      else
      {

        pl->dir = blinky(XB * 28 + YB, pl->list[pl->n],game->map, XB * 28 + YB  -1);

      }
    }
  }



}
