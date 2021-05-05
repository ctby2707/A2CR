#include "game_init.h"
#include "GTK.h"
#include "Close_pacgum.h"
#include "Detect_ghost.h"

char Naif_Agent(Game *game)
{
  int X,Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int Xb, Yb; //ghostpos
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &Xb, &Yb);
  int Xi, Yi;
  pixel_To_MatCoord(game->inky.x, game->inky.y, &Xi, &Yi);
  int Xc, Yc;
  pixel_To_MatCoord(game->clyde.x, game->clyde.y, &Xc, &Yc);
  int Xp, Yp;
  pixel_To_MatCoord(game->pinky.x, game->pinky.y, &Xp, &Yp);

  int dir[4];
  dir[0] = find_ghosts(game->map, X*28+Y, 'N', Xb*28+Yb, Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  dir[1] = find_ghosts(game->map, X*28+Y, 'S', Xb*28+Yb, Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  dir[2] = find_ghosts(game->map, X*28+Y, 'W', Xb*28+Yb, Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  dir[3] = find_ghosts(game->map, X*28+Y, 'E', Xb*28+Yb, Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);

  if(game->chase != 0)
  {
    if(dir[0] == 1)
      return 'N';
    if(dir[1] == 1)
      return 'S';
    if(dir[2] == 1)
      return 'W';
    if(dir[3] == 1)
      return 'E';
  }

  int res = find_close_pac_gum(game->map, X*28+Y, dir);
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
